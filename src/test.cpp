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
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
  std::cout << std::endl;
  std::cout << "base64 encode/decode tool" << std::endl;
  std::cout << std::endl;

  // Parse command-line arguments
  const std::vector<std::string> args(argv + 1, argv + argc);

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

  std::string str = args[0].data();
  std::cout << "base64 in:     " << str << std::endl;

  // Store some data...
  std::vector<Base64::BYTE> myData;

  for (auto i = str.begin(); i != str.end(); i++)
  {
    myData.push_back(*i);
  }

  // Encode it...
  std::string encodedData = Base64::Encode(&myData[0], myData.size());

  std::cout << "base64 encode: " << encodedData << std::endl;

  // Decode it...
  std::vector<Base64::BYTE> decodedData = Base64::Decode(encodedData);

  std::string out;

  for (auto i = decodedData.begin(); i != decodedData.end(); i++)
  {
    out.push_back(*i);
  }

  std::cout << "base64 decode: " << out << std::endl;

  // Destroy all data
  // args.clear();
  str.clear();
  myData.clear();
  encodedData.clear();
  decodedData.clear();
  out.clear();

  std::cout << std::endl;

  // Compare bits (from CMakeRC)

  // std::ifstream file{argv[1], std::ios_base::binary};
  // if (!file) {
  //     std::cerr << "Invalid filename passed to flower: " << argv[1] << '\n';
  //     return 2;
  // }

  // using iter         = std::istreambuf_iterator<char>;
  // const auto fs_size = std::distance(iter(file), iter());
  // file.seekg(0);

  // auto       fs        = cmrc::flower::get_filesystem();
  // auto       flower_rc = fs.open("flower.jpg");
  // const auto rc_size   = std::distance(flower_rc.begin(), flower_rc.end());

  // if (rc_size != fs_size) {
  //     std::cerr << "Flower file sizes do not match: FS == " << fs_size << ", RC == " << rc_size
  //               << "\n";
  //     return 1;
  // }

  // if (!std::equal(flower_rc.begin(), flower_rc.end(), iter(flower_fs))) {
  //     std::cerr << "Flower file contents do not match\n";
  //     return 1;
  // }


  // Get File data

  // for (int i = 1; i <= 5; i++)
  // {
  //   myData.push_back(i);
  // }

  // std::cout << "Size : " << myData.size();
  // std::cout << "\nCapacity : " << myData.capacity();
  // std::cout << "\nMax_Size : " << myData.max_size();

  // // resizes the vector size to 4
  // myData.resize(4);

  // // prints the vector size after resize()
  // std::cout << "\nSize : " << myData.size();

  // // checks if the vector is empty or not
  // if (myData.empty() == false)
  // {
  //   std::cout << "\nVector is not empty";
  // }
  // else
  // {
  //   std::cout << "\nVector is empty";
  // }

  // // Shrinks the vector
  // myData.shrink_to_fit();

  // std::cout << "\nVector elements are: ";

  // for (auto it = myData.begin(); it != myData.end(); it++)
  // {
  //   std::cout << *it << " ";
  // }

  return EXIT_SUCCESS;
}
