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

#include <string>
#include <vector>

namespace base64
{
namespace commands
{

// TODO:
enum Mode {
  INPUT,
  ENCODE,
  DECODE,
  DIFFED, // Check the difference between the input data and the encode/decode output, if any.
  OUTPUT
};

void parse(int argc, char* argv[]);

const std::vector<std::string>& input_files();
bool show_ends();
bool show_line_numbers();

// TODO:
bool show_version();
// TODO:
bool show_help();

} // namespace commands
} // namespace base64
