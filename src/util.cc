#include "util.h"


bool validateProp(const Napi::Env& env, bool isCorrect, const char* propName) {
  if (!isCorrect) {
    char str[255];
    sprintf(str, "%s is not valid", propName);

    Napi::TypeError::New(env, str).ThrowAsJavaScriptException();
  }

  return isCorrect;
}

bool validatePropsLength(const Napi::Env& env, const Napi::CallbackInfo &info, unsigned int minLength) {
  if (info.Length() < minLength) {
    Napi::TypeError::New(env, "Not enough arguments").ThrowAsJavaScriptException();
    return false;
  }
  return true;
}

float getFloatProperty(const Napi::Object& obj, const char* name, float defaultValue) {
  Napi::Value val = obj.Get(name);
   if (val.IsNumber()) {
    return val.As<Napi::Number>().FloatValue() ;
  }
  return defaultValue;
}

int32_t getIntProperty(const Napi::Object& obj, const char* name, int32_t defaultValue) {
  Napi::Value val = obj.Get(name);
   if (val.IsNumber()) {
    return val.As<Napi::Number>().Int32Value();
  }
  return defaultValue;
}
