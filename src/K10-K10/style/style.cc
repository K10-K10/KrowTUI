#include <K10-K10/core/screen.h>

namespace terminal::style {
std::string Style::convert_to_ansi(const terminal::style::Color& color,
                                   bool is_fg) {
  int base = is_fg ? 30 : 40;
  int ext = is_fg ? 38 : 48;

  if (color.type == terminal::style::Color::Type::Basic) {
    if (color.basic == terminal::style::BasicColor::Default) {
      return "\033[" + std::to_string(base + 9) + "m";  // 39m or 49m
    }
    return "\033[" + std::to_string(base + static_cast<int>(color.basic) - 1) +
           "m";
  } else if (color.type == terminal::style::Color::Type::Extended256) {
    return "\033[" + std::to_string(ext) + ";5;" +
           std::to_string(color.code256) + "m";
  } else {
    return "\033[" + std::to_string(ext) + ";2;" + std::to_string(color.r) +
           ";" + std::to_string(color.g) + ";" + std::to_string(color.b) + "m";
  }
}
}  // namespace terminal::style
