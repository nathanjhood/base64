/**
 * @file base32.h
 * @author
 * @brief
 * @version 0.1
 * @date 2023-12-29
 *
 * @copyright Copyright (C) 2023 Nathan J. Hood
 *
 */

#ifndef BASE32_H_
#define BASE32_H_

#include <vector>
#include <string>

/**
 * @brief The base32 namespace.
 *
 */
namespace base32 {

/**
 * @brief The base32 data type.
 *
 */
typedef unsigned char BYTE;

/**
 * @brief Returns a base32-encoded std::string from an array (or std::vector) of unsigned chars.
 *
 * @param buf
 * @param bufLen
 * @return std::string
 *
 * @note This signature carries the actual function definition.
 */
std::string encode(const base32::BYTE* buf, unsigned int bufLen); // definition

/**
 * @brief Returns a base32-decoded std::vector (an array) of unsigned chars from another std::vector of unsigned chars.
 *
 * @param s
 * @return std::vector<base32::BYTE>
 *
 * @note This signature is an overloaded function definition (the actual definition is static).
 */
std::vector<base32::BYTE> decode(const std::vector<base32::BYTE>& s);

/**
 * @brief Returns a base32-encoded std::string from another std::string.
 *
 * @param s
 * @return std::string
 *
 * @note This signature is an overloaded function definition.
 */
std::string encode(std::string const& s);

/**
 * @brief Returns a base32-decoded std::vector (an array) of unsigned chars from an std::string.
 *
 * @param s
 * @return std::vector<base32::BYTE>
 *
 * @note This signature is an overloaded function definition (the actual definition is static).
 */
std::vector<base32::BYTE> decode(const std::string& s);


// Interfaces with std::string_view rather than const std::string&
// Requires C++17
#if __cplusplus >= 201703L
/**
 * @brief Returns a base32-encoded std::string from an std::string_view.
 *
 * @param s
 * @return std::string
 *
 * @note This signature is an overloaded function definition.
 */
std::string encode(std::string_view const& s);

/**
 * @brief Returns a base32-decoded std::vector (an array) of unsigned chars from an std::string_view.
 *
 * @param s
 * @return std::vector<base32::BYTE>
 *
 * @note This signature is an overloaded function definition (the actual definition is static).
 */
std::vector<base32::BYTE> decode(std::string_view const& s); // overload (definition is static)

#endif // __cplusplus >= 201703L

} // namespace base32

#endif // BASE32_H_
