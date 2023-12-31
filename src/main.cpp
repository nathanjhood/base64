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

#include <base64/base64.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
  // Parse command-line arguments
  std::vector<std::string> args(argv + 1, argv + argc);

  // if(
  //     (args[0].data() == "-h") ||
  //     (args[0].data() == "--help")
  //   ) {
  //   std::cout << std::endl;
  //   std::cout << "base64 encode/decode tool" << std::endl;
  //   std::cout << std::endl;
  //   std::cout << "usage: base64 [OPTION]... [FILE]..." << std::endl;
  //   std::cout << std::endl;
  //   std::cout << Base64::copyright << std::endl;
  //   std::cout << std::endl;
  //   return EXIT_SUCCESS;
  // } else if(
  //   (args[0].data() == "-v") ||
  //   (args[0].data() == "--version")
  //   ) {
  //   std::cout << "base64 v0.0.0" << std::endl;
  //   std::cout << std::endl;
  //   return EXIT_SUCCESS;
  // }

  if (args.size() < 1) {

    const char* msg = "base64: missing input string argument!\n"
                      "usage: base64 <input_string> ...\n";
    std::cerr << msg;
    return EXIT_FAILURE;

  } else if (args.size() > 64) {

    const char* msg = "base64: too many input string arguments!\n"
                      "usage: base64 <input_string> ...\n";
    throw std::runtime_error(msg);
    return EXIT_FAILURE;
  }

  // Read files passed as arguments on the command line
  for (auto i = 0; i < args.size(); ++i) {

    // while (args[i].data() == "--verbose") {
    //   std::cout << std::endl;
    //   std::cout << "file: " << args[i].data() << std::endl;
    //   std::cout << std::endl;
    //   args[i].erase(i);
    // }

    std::string line;
    std::ifstream file;
    auto filename = args[i].data();

    // args.data() could be "package.json" or so...
    file.open(filename);

    // Error if file cannot be opened for any reason
    if (!file.is_open()) {
      std::cerr << "base64: could not open input file '" << args[i] << "'!\n";
      return EXIT_FAILURE;
    }

    // Read file line by line
    while (std::getline(file, line)) {

      // Store the data...
      std::vector<Base64::BYTE> myData;

      for (auto i = line.begin(); i != line.end(); i++)
      {
        myData.push_back(*i);
      }

      // Encode it...
      std::string encodedData = Base64::Encode(&myData[0], myData.size());

      // // TODO: Encode it to a vector in contiquous memory...
      // std::vector<Base64::BYTE> encodedData = Base64::Encode(&myData[0], myData.size());

      // Decode it...
      std::vector<Base64::BYTE> decodedData = Base64::Decode(encodedData.data());

      // // TODO: Decode it to a vector in contiquous memory...
      // std::vector<Base64::BYTE> decodedData = Base64::Decode(encodedData);

      // Pass it back out...
      std::string out;

      for (auto i = decodedData.begin(); i != decodedData.end(); i++)
      {
        out.push_back(*i);
      }

      // if(args[0] == "--encode") { /** Log encode output */} else
      // if(args[0] == "--decode") { /** Log decode output */}

      std::cout << /**"base64 encode: " << */ encodedData << std::endl;
      // std::cout << "base64 decode: " << out << std::endl;

      // Destroy all data
      myData.clear();
      encodedData.clear();
      decodedData.clear();
      out.clear();
    }

    // Close the file
    file.close();

    std::cout << std::endl;
  }

  return EXIT_SUCCESS;
}
