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
