#include <K10-K10/style/style.h>

namespace krow::style {

std::string Style::convert_to_ansi(const krow::style::Color& color,
                                   bool is_fg) {
  int base = is_fg ? 30 : 40;
  int ext = is_fg ? 38 : 48;

  if (color.type == krow::style::Color::Type::Basic) {
    if (color.basic == krow::style::BasicColor::Default) {
      return std::to_string(base + 9);
    }
    return std::to_string(base + static_cast<int>(color.basic) - 1);
  } else if (color.type == krow::style::Color::Type::Extended256) {
    return std::to_string(ext) + ";5;" + std::to_string(color.code256);
  } else {
    return std::to_string(ext) + ";2;" + std::to_string(color.r) + ";" +
           std::to_string(color.g) + ";" + std::to_string(color.b);
  }
}

}  // namespace krow::style
