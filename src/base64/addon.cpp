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

// Required header and C++ flag
#if __has_include(<napi.h>) && BUILDING_NODE_EXTENSION

#include "base64/version.h"
#include "base64.cpp"

#include <napi.h>

namespace base64 {

namespace addon {

Napi::Value Hello(const Napi::CallbackInfo& info)
{
  return Napi::String::New(info.Env(), "base64 is online!");
}

Napi::Value Version(const Napi::CallbackInfo& info)
{
  return Napi::String::New(info.Env(), base64_VERSION);
}

/**
 * @brief
 *
 * @param info
 * @return Napi::Value
 */
Napi::Value Encode(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();

  // Arguments required: at least one, and no more than two
  if (info.Length() < 1)
  {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  // Param 1 must be the string to encode
  if (!info[0].IsString())
  {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  // Param 2 (if any) must be boolean. If unset, non-URL alphabet is used.
  if (!info[1].IsBoolean() && info.Length() > 1)
  {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  // Construct a string to hold the encoder's output
#if HAS_STRING_VIEW_H
  std::string_view encodedArg;
#else
  std::string      encodedArg;
#endif

  // Set whether to use the URL alphabet or not...
  // If an option was passed, use it. Else, set to 'false'.
  bool urlMode = info[1] != NULL ? info[1] : false;

  try {
    // Try to encode the string
    encodedArg = base64::encode(info[0].As<Napi::String>(), urlMode);
  } catch (const std::exception &x) {
    // If there was an error...
    std::string message(x.what());
    message += '\n';
    message += "base64: could not encode the following input argument:\n";
    message += info[0].As<Napi::String>();
    Napi::TypeError::New(env, message).ThrowAsJavaScriptException();
    message.clear();
    return env.Null();
  }

  // Construct a Napi string containing the encoder output
  Napi::String out = Napi::String::New(env, encodedArg.data());

#if !HAS_STRING_VIEW_H
  // Clear the old string
  encodedArg.clear();
#endif

  // Return the Napi string
  return out;
}

/**
 * @brief
 *
 * @param info
 * @return Napi::Value
 */
Napi::Value Decode(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();

  // Arguments required: at least one, and no more than two
  if (info.Length() < 1)
  {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  // Param 1 must be the string to encode
  if (!info[0].IsString())
  {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  // Param 2 (if any) must be boolean. If unset, non-URL alphabet is used.
  if (!info[1].IsBoolean() && info.Length() > 1)
  {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  // Construct a fancy char array to hold the decoder's output
  std::vector<base64::BYTE> decodedArg;

  try {
    // Try to decode the string
    decodedArg = base64::decode(info[0].As<Napi::String>());
  } catch (const std::exception &x) {
    // If there was an error...
    std::string message(x.what());
    message += '\n';
    message += "base64: could not decode the following input argument:\n";
    message += info[0].As<Napi::String>();
    Napi::TypeError::New(env, message).ThrowAsJavaScriptException();
    message.clear();
    return env.Null();
  }

  // Construct a Napi string containing the decoder output
  Napi::String out = Napi::String::New(env, reinterpret_cast<const char*>(decodedArg.data()));

  // Clear the old array
  decodedArg.clear();

  // Return the string
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
//   return base64::_encode<Napi::String>(s.As<std::string>());
// }
// template std::string base64::encode(const Napi::String& s);

// /**
//  * @brief
//  *
//  * @param s
//  * @return std::vector<base64::BYTE>
//  */
// std::vector<base64::BYTE> decode(const Napi::String& s) {
//   return base64::_decode<Napi::String>(s.As<std::string>());
// }
// template std::vector<base64::BYTE> base64::decode(const Napi::String& s);

Napi::String byte_vector_to_napi_string(const std::vector<base64::BYTE>& b) {

  auto in = (const char *)b.data();
  Napi::String out;

  return out;
}

static std::vector<base64::BYTE> napi_string_to_byte_vector(const Napi::String& s) {
  std::vector<base64::BYTE> out;
  return out;
}

} // namespace base64

#else
 #error "Warning: Cannot find '<napi.h>'"
#endif // __has_include(<napi.h>) && BUILDING_NODE_EXTENSION
