/**
 * @file base64.h
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

#ifndef BASE_64_H_
#define BASE_64_H_

#include <vector>
#include <string>

#if __has_include(<string_view>)
 #define HAS_STRING_VIEW_H 1
#else
 #define HAS_STRING_VIEW_H 0
 #warning "Warning: Cannot find '<string_view>' in the include path... using less secure <string> instead"
#endif

/**
 * @brief The base64 namespace.
 *
 */
namespace base64 {

/**
 * @brief The base64 data type.
 *
 */
typedef unsigned char BYTE;

base64::BYTE to_byte(char c) {
  return c;
}

base64::BYTE to_byte(unsigned char c) {
  return c;
}

char to_char(base64::BYTE b) {
  return b;
}

// static unsigned char to_unsigned_char(char c) {
//   return c;
// }

/**
 * @brief Returns a base64-encoded std::string from an array (or std::vector) of unsigned chars.
 *
 * @param buf
 * @param bufLen
 * @return std::string
 *
 * @note This signature carries the actual function definition.
 */
std::string encode(const base64::BYTE* buf, unsigned int bufLen, bool url = false); // definition

/**
 * @brief Returns a base64-decoded std::vector (an array) of unsigned chars from another std::vector of unsigned chars.
 *
 * @param s
 * @return std::vector<base64::BYTE>
 *
 * @note This signature is an overloaded function definition (the actual definition is static).
 */
std::vector<base64::BYTE> decode(const std::vector<base64::BYTE>& s, bool url = false);

/**
 * @brief Returns a base64-encoded std::string from another std::string.
 *
 * @param s
 * @return std::string
 *
 * @note This signature is an overloaded function definition.
 */
std::string encode(std::string const& s, bool url = false);

/**
 * @brief Returns a base64-decoded std::vector (an array) of unsigned chars from an std::string.
 *
 * @param s
 * @return std::vector<base64::BYTE>
 *
 * @note This signature is an overloaded function definition (the actual definition is static).
 */
std::vector<base64::BYTE> decode(const std::string& s, bool url = false);


// Interfaces with std::string_view rather than const std::string&
// Requires C++17
#if HAS_STRING_VIEW_H
/**
 * @brief Returns a base64-encoded std::string from an std::string_view.
 *
 * @param s
 * @return std::string
 *
 * @note This signature is an overloaded function definition.
 */
std::string encode(std::string_view const& s, bool url = false);

/**
 * @brief Returns a base64-decoded std::vector (an array) of unsigned chars from an std::string_view.
 *
 * @param s
 * @return std::vector<base64::BYTE>
 *
 * @note This signature is an overloaded function definition (the actual definition is static).
 */
std::vector<base64::BYTE> decode(std::string_view const& s, bool url = false); // overload (definition is static)

#endif // HAS_STRING_VIEW_H

} // namespace base64

#endif // BASE_64_H_
