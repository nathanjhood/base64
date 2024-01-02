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

/**
 * @brief Returns a base64-encoded std::string from an array (or std::vector) of unsigned chars.
 *
 * @param buf
 * @param bufLen
 * @return std::string
 *
 * @note This signature carries the actual function definition.
 */
std::string encode(const base64::BYTE* buf, unsigned int bufLen); // definition

/**
 * @brief Returns a base64-decoded std::vector (an array) of unsigned chars from another std::vector of unsigned chars.
 *
 * @param s
 * @return std::vector<base64::BYTE>
 *
 * @note This signature is an overloaded function definition (the actual definition is static).
 */
std::vector<base64::BYTE> decode(const std::vector<base64::BYTE>& s);

/**
 * @brief Returns a base64-encoded std::string from another std::string.
 *
 * @param s
 * @return std::string
 *
 * @note This signature is an overloaded function definition.
 */
std::string encode(std::string const& s);

/**
 * @brief Returns a base64-decoded std::vector (an array) of unsigned chars from an std::string.
 *
 * @param s
 * @return std::vector<base64::BYTE>
 *
 * @note This signature is an overloaded function definition (the actual definition is static).
 */
std::vector<base64::BYTE> decode(const std::string& s);


// Interfaces with std::string_view rather than const std::string&
// Requires C++17
#if __cplusplus >= 201703L
/**
 * @brief Returns a base64-encoded std::string from an std::string_view.
 *
 * @param s
 * @return std::string
 *
 * @note This signature is an overloaded function definition.
 */
std::string encode(std::string_view const& s);

/**
 * @brief Returns a base64-decoded std::vector (an array) of unsigned chars from an std::string_view.
 *
 * @param s
 * @return std::vector<base64::BYTE>
 *
 * @note This signature is an overloaded function definition (the actual definition is static).
 */
std::vector<base64::BYTE> decode(std::string_view const& s); // overload (definition is static)

#endif // __cplusplus >= 201703L

} // namespace base64

#endif // BASE_64_H_
