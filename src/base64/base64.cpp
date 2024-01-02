/**
 * @file base64.cpp
 * @author René Nyffenegger (rene.nyffenegger@adp-gmbh.ch)
 * @author Nathan J. Hood   (nathanjhood@googlemail.com)
 * @version 0.1
 * @date 2023-12-29
 *
 * @copyright Copyright (C) 2004-2008 René Nyffenegger (original functions)
 * @copyright Copyright (C) 2023       Nathan J. Hood  (revisions)
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

#include "base64/base64.hpp"

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

/**
 * @brief Convert a char to an unsigned char without casting.
 *
 * @param c
 * @return unsigned char
 */
static unsigned char to_unsigned_char(char c) {
  return c;
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
  base64::BYTE stream[3];
  base64::BYTE index[4];

  out.reserve(bufLen);

  while (bufLen--) {

    stream[i++] = *(buf++);

    if (i == 3) {
      index[0] = base64::alphabet[( to_unsigned_char(stream[0]) >> 2)                                       & 0x3f];
      index[1] = base64::alphabet[((to_unsigned_char(stream[0]) << 4) + (to_unsigned_char(stream[1]) >> 4)) & 0x3f];
      index[2] = base64::alphabet[((to_unsigned_char(stream[1]) << 2) + (to_unsigned_char(stream[2]) >> 6)) & 0x3f];
      index[3] = base64::alphabet[  to_unsigned_char(stream[2])                                             & 0x3f];

      for(i = 0; (i < 4) ; i++)
        out += index[i];
      i = 0;
    }
  }

  if (i)
  {
    for(j = i; j < 3; j++)
      stream[j] = '\0';

    index[0] = base64::alphabet[( to_unsigned_char(stream[0]) >> 2)                                        & 0x3f];
    index[1] = base64::alphabet[((to_unsigned_char(stream[0]) << 4) + ( to_unsigned_char(stream[1]) >> 4)) & 0x3f];
    index[2] = base64::alphabet[((to_unsigned_char(stream[1]) << 2) + ( to_unsigned_char(stream[2]) >> 6)) & 0x3f];
    index[3] = base64::alphabet[  to_unsigned_char(stream[2])                                              & 0x3f];

    for (j = 0; (j < i + 1); j++)
      out += index[j];

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
  base64::BYTE stream[3];
  out.reserve(in_len);

  while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {

    index[i++] = encoded_string[in_];
    in_++;

    if (i == 4) {
      for (i = 0; i < 4; i++)
        index[i] = base64::alphabet.find(index[i]);

      stream[0] = (to_unsigned_char(index[0]) << 2) + (to_unsigned_char(index[1]) >> 4);
      stream[1] = (to_unsigned_char(index[1]) << 4) + (to_unsigned_char(index[2]) >> 2);
      stream[2] = (to_unsigned_char(index[2]) << 6) +  to_unsigned_char(index[3]);

      for (i = 0; (i < 3); i++)
          out.emplace_back(stream[i]);
      i = 0;
    }
  }

  if (i) {
    for (j = i; j < 4; j++)
      index[j] = 0;

    for (j = 0; j < 4; j++)
      index[j] = base64::alphabet.find(index[j]);

    stream[0] = (to_unsigned_char(index[0]) << 2) + (to_unsigned_char(index[1]) >> 4);
    stream[1] = (to_unsigned_char(index[1]) << 4) + (to_unsigned_char(index[2]) >> 2);
    stream[2] = (to_unsigned_char(index[2]) << 6) +  to_unsigned_char(index[3]);

    for (j = 0; (j < i - 1); j++)
      out.emplace_back(stream[j]);
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
