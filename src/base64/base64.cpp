/**
 * @file base64.cpp
 * @author René Nyffenegger (rene.nyffenegger@adp-gmbh.ch)
 * @version 0.1
 * @date 2023-12-29
 *
 * @copyright Copyright (C) 2004-2008 René Nyffenegger
 *
 * This source code is provided 'as-is', without any express or implied
 * warranty. In no event will the author be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this source code must not be misrepresented; you must not
 *    claim that you wrote the original source code. If you use this source code
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original source code.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * @brief eg
 * ```
 * std::vector<BYTE> myData;
 * ...
 * std::string encodedData = base64_encode(&myData[0], myData.size());
 * std::vector<BYTE> decodedData = base64_decode(encodedData);
 *
 */

#include <base64/base64.h>
#include <iostream>

namespace Base64
{

/**
 * @brief The base64 charset.
 * ```
 * "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
 * ```
 * @note This is a static member (no header signature declaration).
 */
static const std::string alphabet =
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
  "abcdefghijklmnopqrstuvwxyz"
  "0123456789"
  "+/";


/**
 * @brief
 *
 * @param c
 * @return true
 * @return false
 */
static inline bool isBase64(Base64::BYTE c)
{
  return (isalnum(c) || (c == '+') || (c == '/'));
}

/**
 * @brief
 *
 * @param c
 * @return true
 * @return false
 *
 * @note This is a static member (no header signature declaration).
 */
static inline bool isBase64URL(Base64::BYTE c)
{
  return (isalnum(c) || (c == '-') || (c == '_'));
}

template <typename String>
/**
 * @brief
 *
 * @tparam String - can be used with String = const std::string& or std::string_view (requires at least C++17)
 * @param s
 * @return std::string
 *
 * @note This is a static method (no header signature declaration).
 */
static std::string Encode(String s)
{
  return Base64::Encode(reinterpret_cast<const Base64::BYTE*>(s.data()), s.length());
}


/**
 * @brief
 *
 * @param buf
 * @param bufLen
 * @return std::string
 *
 * @snippet
 * std::vector<BYTE> myData;
 * ...
 * std::string encodedData = Base64::Encode(&myData[0], myData.size());
 * std::vector<BYTE> decodedData = Base64::Decode(encodedData);
 */
std::string Encode(const Base64::BYTE* buf, unsigned int bufLen)
{
  std::string ret;
  int i = 0;
  int j = 0;
  Base64::BYTE octet[3];
  Base64::BYTE index[4];

  while (bufLen--) {
    octet[i++] = *(buf++);
    if (i == 3) {
      index[0] = ( octet[0] & 0xfc) >> 2;
      index[1] = ((octet[0] & 0x03) << 4) + ((octet[1] & 0xf0) >> 4);
      index[2] = ((octet[1] & 0x0f) << 2) + ((octet[2] & 0xc0) >> 6);
      index[3] =   octet[2] & 0x3f;

      for(i = 0; (i <4) ; i++)
        ret += Base64::alphabet[index[i]];
      i = 0;
    }
  }

  if (i)
  {
    for(j = i; j < 3; j++)
      octet[j] = '\0';

    index[0] = ( octet[0] & 0xfc) >> 2;
    index[1] = ((octet[0] & 0x03) << 4) + ((octet[1] & 0xf0) >> 4);
    index[2] = ((octet[1] & 0x0f) << 2) + ((octet[2] & 0xc0) >> 6);
    index[3] =   octet[2] & 0x3f;

    for (j = 0; (j < i + 1); j++)
      ret += Base64::alphabet[index[j]];

    while((i++ < 3))
      ret += '=';
  }

  return ret;
}

/**
 * @brief
 *
 * @param encoded_string
 * @return std::vector<Base64::BYTE>
 */
std::vector<Base64::BYTE> Decode(const std::string& encoded_string)
{
  int in_len = encoded_string.size();
  int i = 0;
  int j = 0;
  int in_ = 0;
  Base64::BYTE index[4];
  Base64::BYTE octet[3];
  std::vector<Base64::BYTE> ret;

  while (in_len-- && ( encoded_string[in_] != '=') && Base64::isBase64(encoded_string[in_])) {
    index[i++] = encoded_string[in_]; in_++;
    if (i ==4) {
      for (i = 0; i <4; i++)
        index[i] = Base64::alphabet.find(index[i]);

      octet[0] = ( index[0]        << 2) + ((index[1] & 0x30) >> 4);
      octet[1] = ((index[1] & 0xf) << 4) + ((index[2] & 0x3c) >> 2);
      octet[2] = ((index[2] & 0x3) << 6) +   index[3];

      for (i = 0; (i < 3); i++)
          ret.push_back(octet[i]);
      i = 0;
    }
  }

  if (i) {
    for (j = i; j <4; j++)
      index[j] = 0;

    for (j = 0; j <4; j++)
      index[j] = Base64::alphabet.find(index[j]);

    octet[0] = ( index[0]        << 2) + ((index[1] & 0x30) >> 4);
    octet[1] = ((index[1] & 0xf) << 4) + ((index[2] & 0x3c) >> 2);
    octet[2] = ((index[2] & 0x3) << 6) +   index[3];

    for (j = 0; (j < i - 1); j++) ret.push_back(octet[j]);
  }

  return ret;
}
/**
 * @brief
 *
 * @param s
 * @param url
 * @return std::string
 *
* @snippet
 * std::string myData;
 * ...
 * std::string encodedData = Base64::Encode(myData);
 * std::vector<BYTE> decodedData = Base64::Decode(encodedData);
 */
std::string Encode(std::string const& s)
{
  return Base64::Encode<std::string>(s);
}

// static const char* copyright =
//  "base64 lib Copyright (C) 2004-2008 René Nyffenegger <rene.nyffenegger@adp-gmbh.ch>"
//  "\n"
//  "base64 cli Copyright (C) 2023 Nathan J. Hood <nathanjhood@googlemail.com>"
//  "\n"
//  "\n"
//  "This source code is provided 'as-is', without any express or implied warranty. In no event will the author be held liable for any damages arising from the use of this software."
//  "\n"
//  "\n"
//  "Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:"
//  "\n"
//  "1. The origin of this source code must not be misrepresented; you must not claim that you wrote the original source code. If you use this source code in a product, an acknowledgment in the product documentation would be appreciated but is not required."
//  "\n"
//  "2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original source code."
//  "\n"
//  "3. This notice may not be removed or altered from any source distribution.";

// std::string Encode(const unsigned char* bytes_to_encode, unsigned int in_len)
// {
//   std::string ret;
//   int i = 0;
//   int j = 0;
//   unsigned char char_array_3[3];
//   unsigned char char_array_4[4];

//   while (in_len--) {
//     char_array_3[i++] = *(bytes_to_encode++);
//     if (i == 3) {
//       char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
//       char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
//       char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
//       char_array_4[3] = char_array_3[2] & 0x3f;

//       for(i = 0; (i <4) ; i++)
//         ret += Base64::chars[char_array_4[i]];
//       i = 0;
//     }
//   }

//   if (i)
//   {
//     for(j = i; j < 3; j++)
//       char_array_3[j] = '\0';

//     char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
//     char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
//     char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
//     char_array_4[3] = char_array_3[2] & 0x3f;

//     for (j = 0; (j < i + 1); j++)
//       ret += Base64::chars[char_array_4[j]];

//     while((i++ < 3))
//       ret += '=';

//   }

//   return ret;

// }

// std::string Decode(std::string const& encoded_string)
// {
//   int in_len = encoded_string.size();
//   int i = 0;
//   int j = 0;
//   int in_ = 0;
//   unsigned char char_array_4[4], char_array_3[3];
//   std::string ret;

//   while (in_len-- && ( encoded_string[in_] != '=') && isBase64(encoded_string[in_])) {
//     char_array_4[i++] = encoded_string[in_]; in_++;
//     if (i ==4) {
//       for (i = 0; i <4; i++)
//         char_array_4[i] = Base64::chars.find(char_array_4[i]);

//       char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
//       char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
//       char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

//       for (i = 0; (i < 3); i++)
//         ret += char_array_3[i];
//       i = 0;
//     }
//   }

//   if (i) {
//     for (j = i; j <4; j++)
//       char_array_4[j] = 0;

//     for (j = 0; j <4; j++)
//       char_array_4[j] = Base64::chars.find(char_array_4[j]);

//     char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
//     char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
//     char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

//     for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
//   }

//   return ret;
// }

} // namespace Base64
