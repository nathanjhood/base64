/**
 * @file cli.cpp
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

#include "base64/cli.hpp"
#include "base64/base64.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

namespace base64 {
namespace cli {

static base64::cli::Mode              _mode              = base64::cli::Mode::ENCODE;
static bool                           _mode_is_set       = false;

static std::vector<std::string>       _input_files;
static bool                           _show_line_numbers = false;
static bool                           _show_ends         = false;

static bool                           _show_verbose      = false;
static bool                           _show_version      = false;
static bool                           _show_help         = false;

void parse(int argc, char* argv[]) {

  if (argc < 1) {
    throw std::runtime_error("base64: missing input parameters!");
  }

  if (argc > 64) {
    throw std::runtime_error("base64: too many input parameters!");
  }

  // Args passed validation - pass them to an array...
  const std::vector<std::string> args(argv + 1, argv + argc);

  for (const auto& arg : args) {

    if (_input_files.empty()) {

      if (arg == "-v" || arg == "--version") {
        if (_show_version) {
          throw std::runtime_error("base64: cannot use -v/--version parameter twice!");
        }
        _show_version = true;
        continue;
      }

      if (arg == "-h" || arg == "--help") {
        if (_show_help) {
          throw std::runtime_error("base64: cannot use -h/--help parameter twice!");
        }
        _show_help = true;
        continue;
      }

      if (arg == "--verbose") {
        if (_show_verbose) {
          throw std::runtime_error("base64: cannot use --verbose parameter twice!");
        }
        _show_verbose = true;
        continue;
      }

      if (arg == "-n" || arg == "--number" || arg == "--show-lines") {
        if (_show_line_numbers) {
          throw std::runtime_error("base64: cannot use -n/--number/--show-lines parameter twice!");
        }
        _show_line_numbers = true;
        continue;
      }

      if (arg == "-E" || arg == "--show-ends") {
        if (_show_ends) {
          throw std::runtime_error("base64: cannot use -E/--show-ends parameter twice!");
        }
        _show_ends = true;
        continue;
      }

      if (arg == "--encode") {
        if (_mode_is_set) {
          throw std::runtime_error("base64: cannot use --encode/--decode parameter twice!");
        }
        base64::cli::set_mode(base64::cli::ENCODE);
        _mode_is_set = true;
        continue;
      }

      if (arg == "--decode") {
        if (_mode_is_set) {
          throw std::runtime_error("base64: cannot use --encode/--decode parameter twice!");
        }
        base64::cli::set_mode(base64::cli::DECODE);
        _mode_is_set = true;
        continue;
      }
    }

    if (!std::filesystem::exists(arg)) {
      throw std::runtime_error(std::string("base64: ") + std::string(arg) + ": No such file or directory");
    }

    // Read files passed as arguments on the command line
    _input_files.push_back(arg);
  }
}

static int encode(std::ifstream& input_file, std::string line, int line_count, const std::string &file_name) {

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
    for (auto x : encodedData)
      std::cout << x;

    if (base64::cli::show_ends()) {
      std::cout << '$';
    }

    std::cout << '\n';

    encodedData.clear();
  }

  return EXIT_SUCCESS;
}

static int decode(std::ifstream& input_file, std::string line, int line_count, const std::string &file_name) {

  while (std::getline(input_file, line)) {

    if (base64::cli::show_line_numbers()) {
      std::cout << std::setw(6) << std::setfill(' ') << line_count++ << "  ";
    }

    // Store some data...
    std::vector<base64::BYTE> decodedData;

    try {
      for (auto i = line.begin(); i != line.end(); i++)
      {
        // decodedData.push_back(*i);
        decodedData = base64::decode(line);
      }
    } catch (const std::exception &x) {
      std::cerr << x.what() << '\n';
      std::cerr << "base64: could not decode input file '" << file_name << "'!\n";
      return EXIT_FAILURE;
    }

    // This is the main print-out to stdout
    for (auto x : decodedData)
        std::cout << x;

    if (base64::cli::show_ends()) {
      std::cout << '$';
    }

    std::cout << '\n';

    decodedData.clear();
  }

  return EXIT_SUCCESS;
}

int process(int argc, char* argv[]) {

  int ok = 0;

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

    switch(base64::cli::get_mode())
    {
      case base64::cli::ENCODE:
      ok = encode(input_file, line, line_count, file_name);
      break;

      case base64::cli::DECODE:
      ok = decode(input_file, line, line_count, file_name);
      break;

      default:
      ok = encode(input_file, line, line_count, file_name);
      break;
    }

    line.clear();
    input_file.close();
  }

  return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}

void set_mode(const base64::cli::MODE& m) {
  _mode = m;
  _mode_is_set = true;
}

base64::cli::MODE get_mode() {
  return _mode;
}

const std::vector<std::string>& input_files() {
  return _input_files;
}

bool show_ends() {
  return _show_ends;
}

bool show_line_numbers() {
  return _show_line_numbers;
}

bool show_verbose() {
  return _show_verbose;
}

bool show_version() {
  return _show_version;
}

bool show_help() {
  return _show_help;
}

} // namespace base64
} // namespace commands
