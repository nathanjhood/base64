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
 */

#include "base64/base64.h"

namespace base64 {

/**
 * @brief The base64 alphabet (non-URL).
 *
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
static inline bool is_base64(const base64::BYTE& c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

/**
 * @brief
 *
 * @param c
 * @return true
 * @return false
 */
static inline bool is_base64_url(const base64::BYTE& c) {
  return (isalnum(c) || (c == '-') || (c == '_'));
}

template <typename Str>
/**
 * @brief
 *
 * @tparam Str - can be used with String = const std::string& or std::string_view (requires at least C++17)
 * @param s
 * @return std::string
 *
 * @note This is a static method (no header signature declaration).
 */
static std::string _encode(Str s)
{
  return base64::encode(reinterpret_cast<const base64::BYTE*>(s.data()), s.length());
}

std::string encode(const base64::BYTE* buf, unsigned int bufLen) {

  std::string out;
  int i = 0;
  int j = 0;
  base64::BYTE octet[3];
  base64::BYTE index[4];

  while (bufLen--) {
    octet[i++] = *(buf++);
    if (i == 3) {
      index[0] = ( octet[0] & 0xfc) >> 2;
      index[1] = ((octet[0] & 0x03) << 4) + ((octet[1] & 0xf0) >> 4);
      index[2] = ((octet[1] & 0x0f) << 2) + ((octet[2] & 0xc0) >> 6);
      index[3] =   octet[2] & 0x3f;

      for(i = 0; (i <4) ; i++)
        out += base64::alphabet[index[i]];
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
      out += base64::alphabet[index[j]];

    while((i++ < 3))
      out += '=';
  }

  return out;
}

template <typename Str>
/**
 * @brief
 *
 * @param encoded_string
 * @return std::vector<base64::BYTE>
 *
 * @note This is a static method (no header signature declaration).
 */
static std::vector<base64::BYTE> _decode(const Str& encoded_string) {

  std::vector<base64::BYTE> out;
  int i = 0;
  int j = 0;
  int in_ = 0;
  int in_len = encoded_string.size();
  base64::BYTE index[4];
  base64::BYTE octet[3];

  while (in_len-- && (  encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
    index[i++] = encoded_string[in_]; in_++;
    if (i ==4) {
      for (i = 0; i < 4; i++)
        index[i] = base64::alphabet.find(index[i]);

      octet[0] = ( index[0]        << 2) + ((index[1] & 0x30) >> 4);
      octet[1] = ((index[1] & 0xf) << 4) + ((index[2] & 0x3c) >> 2);
      octet[2] = ((index[2] & 0x3) << 6) +   index[3];

      for (i = 0; (i < 3); i++)
          out.push_back(octet[i]);
      i = 0;
    }
  }

  if (i) {
    for (j = i; j < 4; j++)
      index[j] = 0;

    for (j = 0; j < 4; j++)
      index[j] = base64::alphabet.find(index[j]);

    octet[0] = ( index[0]        << 2) + ((index[1] & 0x30) >> 4);
    octet[1] = ((index[1] & 0xf) << 4) + ((index[2] & 0x3c) >> 2);
    octet[2] = ((index[2] & 0x3) << 6) +   index[3];

    for (j = 0; (j < i - 1); j++) out.push_back(octet[j]);
  }

  return out;
}

std::string encode(const std::string& s) {
  return base64::_encode<std::string>(s);
}

std::vector<base64::BYTE> decode(const std::string& s) {
  return base64::_decode<std::string>(s);
}

std::vector<base64::BYTE> decode(const std::vector<base64::BYTE>& s) {
  return base64::_decode<std::vector<base64::BYTE>>(s);
}

// Interfaces with std::string_view rather than const std::string&
// Requires C++17
#if __cplusplus >= 201703L
std::string encode(const std::string_view& s) {
  return base64::_encode<std::string_view>(s);
}
std::vector<base64::BYTE> decode(const std::string_view& s) {
  return base64::_decode<std::string_view>(s);
}
#endif

template std::string _encode(const std::string& s);
template std::vector<base64::BYTE> _decode(const std::string& encoded_string);
#if __cplusplus >= 201703L
template std::string _encode(const std::string_view& s);
template std::vector<base64::BYTE> _decode(const std::string_view& encoded_string);
#endif

} // namespace base64
