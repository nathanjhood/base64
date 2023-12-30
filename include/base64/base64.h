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
 * @brief eg
 * ```
 * std::vector<BYTE> myData;
 * ...
 * std::string encodedData = base64_encode(&myData[0], myData.size());
 * std::vector<BYTE> decodedData = base64_decode(encodedData);
 *
 */

#ifndef BASE64_H_
#define BASE64_H_

#include <vector>
#include <string>

namespace Base64
{

typedef unsigned char BYTE;

std::string Encode(const Base64::BYTE* buf, unsigned int bufLen);
std::vector<Base64::BYTE> Decode(const std::string& encoded_string);

// static const char *Base64::copyright;
}
#endif // BASE64_H_
