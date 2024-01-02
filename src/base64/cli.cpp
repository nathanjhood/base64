/**
 * @file cli.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-01
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "base64/cli.hpp"

#include <filesystem>
#include <fstream>

namespace base64 {
namespace commands {

static std::vector<std::string>       _input_files;
static bool                           _show_line_numbers = false;
static bool                           _show_ends         = false;

static bool                           _show_version      = false;
static bool                           _show_help         = false;

/**
 * @brief
 *
 * @param argc
 * @param argv
 */
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

      if (arg == "-n" || arg == "--number") {
        if (_show_line_numbers) {
          throw std::runtime_error("base64: cannot use -n/--number parameter twice!");
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
    }

    if (!std::filesystem::exists(arg)) {
      throw std::runtime_error(std::string("dog: ") + std::string(arg) + ": No such file or directory");
    }

    // Read files passed as arguments on the command line
    _input_files.push_back(arg);
  }
}

/**
 * @brief Get the Input Files object.
 *
 * @return const std::vector<std::string>&
 */
const std::vector<std::string>& input_files() {
  return _input_files;
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool show_ends() {
  return _show_ends;
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool show_line_numbers() {
  return _show_line_numbers;
}

bool show_version() {
  return _show_version;
}
bool show_help() {
  return _show_help;
}

} // namespace base64
} // namespace commands
