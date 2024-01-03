/**
 * @file addon.cpp
 * @author Nathan J. Hood (nathanjood@googlemail.com)
 * @brief Exports 'base64' as a binary NodeJS addon.
 * @version 0.1
 * @date 2024-01-03
 *
 * @copyright Copyright (c) 2024 Nathan J. Hood (nathanjood@googlemail.com)
 *
 */

#include "base64/version.h"
#include "base64.cpp"

#include <napi.h>

// #pragma comment( lib, "base64" )

namespace base64 {

namespace addon {

Napi::Value Hello(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();

  return Napi::String::New(env, "base64 is online!");
}

Napi::Value Version(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();

  return Napi::String::New(env, base64_VERSION);
}

Napi::Value Encode(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();

  if (info.Length() < 1)
  {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsString())
  {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  std::string encodedArg;

  try {
    encodedArg = base64::encode(info[0].As<Napi::String>().ToString());
  } catch (const std::exception &x) {
    const char* message = x.what();
    // message += '\n';
    // message += 'b', 'a', 's', 'e', '6', '4', ':';
    // message += ' ', 'c', 'o', 'u', 'l', 'd', ' ', 'n', 'o', 't', ' ', 'd', 'e', 'c', 'o', 'd', 'e';
    // message += ' ', 'i', 'n', 'p', 'u', 't', ' ', 'a', 'r', 'g', 'u', 'm', 'e', 'n', 't', ' ', '=', ' ';
    // message + info[0].As<std::string>();
    Napi::TypeError::New(env, message).ThrowAsJavaScriptException();
    return env.Null();;
  }

  Napi::String out = Napi::String::New(env, encodedArg);
  encodedArg.clear();

  return out;
}

Napi::Value Decode(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();

  if (info.Length() < 1)
  {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsString())
  {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  auto arg = info[0].As<Napi::String>().ToString();

  std::string op(arg);

  std::vector<base64::BYTE> decodedData = base64::decode(op);

  const char* vec = (char *)decodedData.data();

  auto out = Napi::String::New(env, vec);

  op.clear();
  decodedData.clear();

  return out;
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{

  exports.Set(
    Napi::String::New(env, "hello"),
    Napi::Function::New(env, Hello)
  );

  exports.Set(
    Napi::String::New(env, "version"),
    Napi::Function::New(env, Version)
  );

  exports.Set(
    Napi::String::New(env, "encode"),
    Napi::Function::New(env, Encode)
  );

  exports.Set(
    Napi::String::New(env, "decode"),
    Napi::Function::New(env, Decode)
  );

  return exports;
}

NODE_API_MODULE(base64, Init)

} // namespace addon

// Here, we can extend the base64 source file with Napi overloads.

// /**
//  * @brief
//  *
//  * @param s
//  * @return std::string
//  */
// std::string encode(const Napi::String& s) {
//   return base64::_encode<Napi::String>(s);
// }

// /**
//  * @brief
//  *
//  * @param s
//  * @return std::vector<base64::BYTE>
//  */
// std::vector<base64::BYTE> decode(const Napi::String& s) {
//   return base64::_decode<Napi::String>(s);
// }
// template std::string base64::encode(const Napi::String& s);
// template std::vector<base64::BYTE> base64::decode(const Napi::String& s);

} // namespace base64
