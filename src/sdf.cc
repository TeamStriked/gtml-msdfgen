#include "util.h"
#include <iostream>

int z_verbose = 0;

void z_error(char *message)
{
}

Napi::Value generateMSDF(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();

  if (info.Length() < 2)
  {
    Napi::TypeError::New(env, "Not enough arguments")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsBuffer())
  {
    Napi::TypeError::New(env, "Invalid buffer").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[1].IsString())
  {
    Napi::TypeError::New(env, "Invalid string").ThrowAsJavaScriptException();
    return env.Null();
  }

  float maxAngle = 3.0;
  int32_t imageWidth = 32;
  int32_t imageHeight = 32;
  float range = 4.0;
  float scale = 1.0;
  float translationX = 4.0;
  float translationY = 4.0;


  if (info.Length() == 3 && !info[2].IsUndefined())
  {
    if (
        !validateProp(env, info[2].IsObject(), "msdfCnfigFlags"))
    {
      return env.Null();
    }

    Napi::Object config = info[2].As<Napi::Object>();
    maxAngle = getFloatProperty(config, "maxAngle", 3.0);
    imageWidth = getIntProperty(config, "imageWidth", 32);
    imageHeight = getIntProperty(config, "imageHeight", 32);
    range = getFloatProperty(config, "range", 4.0);
    scale = getFloatProperty(config, "scale", 1.0);
    translationX = getFloatProperty(config, "translationX", 4.0);
    translationY = getFloatProperty(config, "translationY", 4.0);
  }


  msdfgen::FreetypeHandle *ft = msdfgen::initializeFreetype();

  Napi::Buffer<unsigned char> buffer = info[0].As<Napi::Buffer<unsigned char>>();
  Napi::String word = info[1].As<Napi::String>();

  msdfgen::FontHandle *font = msdfgen::loadFontData(ft, buffer.Data(),
                                  buffer.Length());
  if (font)
  {
    Napi::Object chars = Napi::Object::New(env);

    std::string str = info[1].ToString().Utf8Value();
    int charId = 0;
    for (char &c : str)
    {
      msdfgen::Shape shape;
      Napi::Object obj = Napi::Object::New(env);

      if (loadGlyph(shape, font, c))
      {
        shape.normalize();
        //max. angle
        msdfgen::edgeColoringSimple(shape, 3.0);
        //image width, height
        msdfgen::Bitmap<float, 3> msdf(32, 32);
        //range, scale, translation
        msdfgen::generateMSDF(msdf, shape, 4.0, 1.0, msdfgen::Vector2(4.0, 4.0));

        const msdfgen::BitmapConstRef<float, 3> bitmap = msdf;

        std::vector<msdfgen::byte> pixels(3 * bitmap.width * bitmap.height);
        std::vector<msdfgen::byte>::iterator it = pixels.begin();

        Napi::Uint8Array array = Napi::Uint8Array::New(env, pixels.size());

        int id = 0;
        for (int y = bitmap.height - 1; y >= 0; --y)
          for (int x = 0; x < bitmap.width; ++x)
          {
            array[id++] = msdfgen::pixelFloatToByte(bitmap(x, y)[0]);
            array[id++] = msdfgen::pixelFloatToByte(bitmap(x, y)[1]);
            array[id++] = msdfgen::pixelFloatToByte(bitmap(x, y)[2]);
          }

        obj.Set("data", array);
        obj.Set("width", bitmap.width);
        obj.Set("height", bitmap.height);

        chars.Set(c, obj);

        charId++;
      }
    }

    msdfgen::destroyFont(font);
    msdfgen::deinitializeFreetype(ft);

    return chars;
  }
  else
  {
    deinitializeFreetype(ft);
    return env.Null();
  }
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("generateMSDF", Napi::Function::New(env, generateMSDF));
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)
