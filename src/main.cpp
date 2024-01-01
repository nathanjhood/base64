/**
 * @file main.cpp
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @brief
 * @version 0.0.0
 * @date 2023-12-30
 *
 * @copyright Copyright (c) 2023 Nathan J. Hood (nathanjhood@googlemail.com)
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
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

namespace base64 {
enum modeSwitcher {
  INPUT,
  ENCODE,
  DECODE,
  DIFFED, // Check the difference between the input data and the encode/decode output, if any.
  OUTPUT
};
}

int main(int argc, char *argv[])
{
  // Parse command-line arguments...
  std::vector<std::string> args(argv + 1, argv + argc);

  if (args.size() < 1) {
    std::cerr << "base64: missing input string argument!" << std::endl;
    std::cerr << "usage: base64 <input_string> ..." << std::endl;
    return EXIT_FAILURE;

  }
  if (args.size() > 64) {
    std::cerr << "base64: too many input string arguments!" << std::endl;
    std::cerr << "usage: base64 <input_string> ..." << std::endl;
    return EXIT_FAILURE;
  }

  // Read files passed as arguments on the command line...
  for (auto i = 0; i < args.size(); ++i) {

    std::string line;
    std::ifstream file;
    auto filename = args[i].data();
    auto mode = base64::modeSwitcher::ENCODE;

    // args.data() could be "package.json" or so...
    file.open(filename);

    // Error if file cannot be opened for any reason...
    if (!file.is_open()) {
      std::cerr << "base64: could not open input file '" << args[i] << "'!\n";
      return EXIT_FAILURE;
    }

    // Read file line by line
    while (std::getline(file, line)) {

      // Store some data...
      std::vector<base64::BYTE> myData;

      for (auto i = line.begin(); i != line.end(); i++)
      {
        myData.push_back(*i);
      }

      // if (mode >= 1) {
        // Encode it...
        std::string encodedData = base64::encode(&myData[0], myData.size());

      // if (mode >= 2) {
        // Decode it...
        std::vector<base64::BYTE> decodedData = base64::decode(myData);

      // if (mode >= 3) {
      // Check for any differences...
      std::vector<base64::BYTE> diffData = base64::decode(encodedData);
      std::string diffedOut;

      for (auto i = line.begin(); i != line.end(); i++)
      {
        if (myData.size() == diffData.size()) {
          diffedOut.push_back((char) 0);
        } else {
          diffedOut.push_back((char) 1);
        };
      }

      // if (mode >= 4) {
      // Pass it back out...
      std::string out;
      for (auto i = decodedData.begin(); i != decodedData.end(); i++)
      {
        out.push_back(*i);
      }

      // Output mode
      switch (mode)
      {
      case base64::modeSwitcher::INPUT:
        for (auto x : myData)
          std::cout << x;
        std::cout << std::endl;
        break;

      case base64::modeSwitcher::ENCODE:

        for (auto x : encodedData)
          std::cout << x;
        std::cout << std::endl;
        break;

      case base64::modeSwitcher::DECODE:
        for (auto x : decodedData)
          std::cout << x;
        std::cout << std::endl;
        break;

      case base64::modeSwitcher::DIFFED:
        for (auto x : diffedOut)
          std::cout << x;
        std::cout << std::endl;
        break;

      case base64::modeSwitcher::OUTPUT:
        for (auto x : out)
          std::cout << x;
        std::cout << std::endl;
        break;

      default:
        for (auto x : encodedData)
          std::cout << x;
        std::cout << std::endl;
        break;
      }

      // Destroy all data...
      out.clear();
      // }
      decodedData.clear();
      // }
      encodedData.clear();
      // }
      myData.clear();
      // } // mode comparison
    }

    // Close the file.
    filename = nullptr;
    file.close();

    std::cout << std::endl;
  }

  return EXIT_SUCCESS;
}
