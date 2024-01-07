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
#include "base64/base64.hpp"

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
 * @param args
 * @return Napi::Value
 */
Napi::Value Encode(const Napi::CallbackInfo& args)
{
  Napi::Env env = args.Env();

  // Arguments required: at least one, and no more than two
  if (args.Length() < 1)
  {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  // Param 1 must be the string to encode
  if (!args[0].IsString())
  {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  // Param 2 (if any) must be boolean. If unset, non-URL alphabet is used.
  if (!args[1].IsBoolean() && args.Length() > 1)
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
  bool urlMode = args[1] != NULL ? args[1] : false;

  try {

    // Try to encode the string
    encodedArg = base64::encode(args[0].ToString(), urlMode);

  } catch (const std::exception &x) {

    // If there was an error...
    std::string message(x.what());
    message += '\n';
    message += "base64: could not encode the following input argument:\n";
    message += args[0].As<Napi::String>();
    Napi::TypeError::New(env, message).ThrowAsJavaScriptException();
    message.clear();
    return env.Null();
  }

  try {

    // Construct a Napi string containing the encoder output
    Napi::String out = Napi::String::New(env, encodedArg.data());
#if !HAS_STRING_VIEW_H
    // Clear the old string
    encodedArg.clear();
#endif
    // Return the Napi string
    return out;

  } catch (const std::exception &x) {

    // If there was an error...
    std::string message(x.what());
    message += '\n';
    message += "base64: could not encode the following input argument:\n";
    message += args[0].As<Napi::String>();

    // Throw a javascript-side exception
    Napi::TypeError::New(env, message).ThrowAsJavaScriptException();

#if !HAS_STRING_VIEW_H
    // Clear the old string
    encodedArg.clear();
#endif
    message.clear();

    // Return null
    return env.Null();
  }
}

/**
 * @brief
 *
 * @param args
 * @return Napi::Value
 */
Napi::Value Decode(const Napi::CallbackInfo& args)
{
  Napi::Env env = args.Env();

  // Arguments required: at least one, and no more than two
  if (args.Length() < 1)
  {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  // Param 1 must be the string to encode
  if (!args[0].IsString())
  {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  // Param 2 (if any) must be boolean. If unset, non-URL alphabet is used.
  if (!args[1].IsBoolean() && args.Length() > 1)
  {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  // Construct a string to hold the arg
  std::string      str(args[0].ToString().Utf8Value());
  bool urlMode = args[1].ToBoolean().Value();

  // Construct a fancy char array to hold the decoder's output
  std::vector<base64::BYTE> decodedArg;

  try {

    decodedArg = base64::decode(str, urlMode);

  } catch (const std::exception &x) {

    // If there was an error...
    std::string message(x.what());
    message += '\n';
    message += "base64: could not decode the following input argument:\n";
    message += args[0].As<Napi::String>();

    // Throw a javascript-side exception
    Napi::TypeError::New(env, message).ThrowAsJavaScriptException();

    // Clear the old array
    decodedArg.clear();
    message.clear();

    // Return null
    return env.Null();
  }

  try {

    // Try to construct a Napi string containing the decoder output
    Napi::String out = Napi::String::New(env, std::string(decodedArg.begin(), decodedArg.end()));

    // Clear the old array
    decodedArg.clear();

    // Return the string
    return out;

  } catch (const std::exception &x) {

    // If there was an error...
    std::string message(x.what());
    message += '\n';
    message += "base64: could not construct the decoded argument into a string:\n";
    message += args[0].As<Napi::String>();

    // Throw a javascript-side exception
    Napi::TypeError::New(env, message).ThrowAsJavaScriptException();

    // Clear the old array
    decodedArg.clear();
    message.clear();

    // Return null
    return env.Null();
  }
}

// Construct an 'initializer' object that carries our functions
Napi::Object Init(Napi::Env env, Napi::Object exports)
{

  // Export a chosen C++ function under a given Javascript key
  exports.Set(
    Napi::String::New(env, "hello"), // Name of function on Javascript side...
    Napi::Function::New(env, Hello)  // Name of function on C++ side...
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

  // The above will expose the C++ function 'Hello' as a javascript function named 'hello', etc...

  return exports;
}

// Register a new addon with the intializer function defined above
NODE_API_MODULE(base64, Init) // (name to use, initializer to use)

// The above attaches the functions exported in 'Init()' to the name used in the fist argument.
// The C++ functions are then obtainable on the Javascript side under e.g. 'base64.hello()'

} // namespace addon

// Here, we can extend the base64 source file with Napi overloads.



} // namespace base64

#else
 #warning "Warning: Cannot find '<napi.h>'"
#endif // __has_include(<napi.h>) && BUILDING_NODE_EXTENSION
