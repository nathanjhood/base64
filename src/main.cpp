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

#include "base64/cli.hpp"
#include "base64/base64.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
  bool ok = true;

  // Parse command-line arguments...
  try {
    base64::cli::parse(argc, argv);
  } catch (const std::exception &x) {
    std::cerr << x.what() << '\n';
    std::cerr << "usage: base64 [-n|--number] [-E|--show-ends] <input_file> ...\n";
    return EXIT_FAILURE;
  }

  // Return the files that were passed in to 'parse()'
  // and iterate through them...
  for (const auto &file_name : base64::cli::input_files()) {

    std::ifstream input_file(file_name.data(), std::ios::in);

    // Error if file cannot be opened for any reason...
    if (!input_file.is_open()) {
      std::cerr << "base64: could not open input file '" << file_name << "'!\n";
      return EXIT_FAILURE;
    }

    std::string line;
    int         line_count = 1;

    // TODO: 'Mode' == ENCODE {...
    while (std::getline(input_file, line)) {

      if (base64::cli::show_line_numbers()) {
        std::cout << std::setw(6) << std::setfill(' ') << line_count++ << "  ";
      }

      // Encode it (note: new string per line found)...
      std::string encodedData;
      encodedData.reserve(line.size());
      try {
        encodedData += base64::encode(line);
      } catch (const std::exception &x) {
        std::cerr << x.what() << '\n';
        std::cerr << "base64: could not encode input file '" << file_name << "'!\n";
        return EXIT_FAILURE;
      }

      // This is the main print-out to stdout
      // std::cout << encodedData.data();
      for (auto x : encodedData)
        std::cout << x;

      if (base64::cli::show_ends()) {
        std::cout << '$';
      }

      std::cout << '\n';

      encodedData.clear();
    }
  //   }

  //   // Close the file.
  //   filename = nullptr;
  //   file.close();

  //   std::cout << std::endl;
  // }

  return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}
