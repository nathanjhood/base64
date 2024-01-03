/**
 * @file cli.hpp
 * @author your name (you@domain.com)
 * @brief https://github.com/mostsignificant/dog
 * @version 0.1
 * @date 2024-01-01
 *
 * @copyright Copyright (c) 2018 Christian Göhring
 * @copyright Copyright (c) 2024 Nathan J. Hood
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#ifndef BASE_64_CLI_H_
#define BASE_64_CLI_H_

#include <string>
#include <vector>

namespace base64
{
namespace cli
{

/**
 * @brief
 * TODO:
 */
enum Mode {
  INPUT,
  ENCODE,
  DECODE,
  DIFFED, // Check the difference between the input data and the encode/decode output, if any.
  OUTPUT
};

typedef Mode MODE;

//           foreground background
// black        30         40
// red          31         41
// green        32         42
// yellow       33         43
// blue         34         44
// magenta      35         45
// cyan         36         46
// white        37         47

const std::string black  ("\033[0;30m");
const std::string red    ("\033[0;31m");
const std::string green  ("\033[0;32m");
const std::string yellow ("\033[0;33m");
const std::string blue   ("\033[0;34m");
const std::string magenta("\033[0;35m");
const std::string cyan   ("\033[0;36m");
const std::string white  ("\033[0;37m");
// reset             0  (everything back to normal)
// bold/bright       1  (often a brighter shade of the same colour)
// underline         4
// inverse           7  (swap foreground and background colours)
// bold/bright off  21
// underline off    24
// inverse off      27

const std::string reset    ("\033[0m");
const std::string bold     ("\033[1m");
const std::string underline("\033[4m");
const std::string inverse  ("\033[7m");
// useage: 'std::cout << cli::red << "red text" << cli::reset << std::endl;'

/**
 * @brief
 *
 * @param argc
 * @param argv
 */
void parse(int argc, char* argv[]);

/**
 * @brief
 *
 * @param argc
 * @param argv
 * @return int \code EXIT_SUCCESS || EXIT_FAILURE \endcode
 */
int process(int argc, char **argv);

/**
 * @brief
 *
 * @return const std::vector<std::string>&
 */
const std::vector<std::string>& input_files();

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool show_ends();

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool show_line_numbers();

/**
 * @brief
 * TODO:
 * @return true
 * @return false
 */
bool show_verbose();

/**
 * @brief
 * TODO:
 * @return true
 * @return false
 */
bool show_version();

/**
 * @brief
 * TODO:
 * @return true
 * @return false
 */
bool show_help();

} // namespace commands
} // namespace base64

#endif // BASE_64_CLI_H_
