/**
 * @file base64.h
 * @author René Nyffenegger (rene.nyffenegger@adp-gmbh.ch)
 * @brief
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

#ifndef BASE64_H_
#define BASE64_H_

#include <vector>
#include <string>

namespace base64 {

typedef unsigned char BYTE;

std::string encode(const base64::BYTE* buf, unsigned int bufLen);                 // definitions
std::vector<base64::BYTE> decode(const std::string& s);

std::string encode(std::string const& s);                                         // overloads

#if __cplusplus >= 201703L
// Interfaces with std::string_view rather than const std::string&
// Requires C++17
std::string encode(std::string_view const& s);
std::vector<base64::BYTE> decode(std::string_view const& s) ;
#endif

}
#endif // BASE64_H_
