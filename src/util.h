#define NAPI_VERSION 3
#include <napi.h>
#include <msdfgen.h>
#include <msdfgen-ext.h>

bool validateProp(const Napi::Env &env, bool isCorrect, const char *propName);
bool validatePropsLength(const Napi::Env &env, const Napi::CallbackInfo &info, unsigned int minLength);
int32_t getIntProperty(const Napi::Object &obj, const char *name, int32_t defaultValue);
float getFloatProperty(const Napi::Object &obj, const char *name, float defaultValue);