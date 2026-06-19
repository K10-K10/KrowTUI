#include <K10-K10/style/color.h>
#include <K10-K10/style/style.h>

#include <array>
#include <string>

namespace krow::style {

std::string Style::convert_to_ansi(const krow::style::Color& color,
                                   const bool is_fg) {
  int base = is_fg ? 30 : 40;
  const int ext = is_fg ? 38 : 48;

  const krow::style::Color::Type t = color.get_type();
  switch (t) {
    case (krow::style::Color::Type::Basic):
      if (color.get_basic() == krow::style::BasicColor::Default) {
        return std::to_string(base + 9);
      }
      return std::to_string(base + static_cast<int>(color.get_basic()) - 1);
    case (krow::style::Color::Type::Extended256):
      return std::to_string(ext) + ";5;" + std::to_string(color.get_code256());
      break;
    default:
      std::array<int, 3> rgb = color.get_rgb();
      return std::to_string(ext) + ";2;" + std::to_string(rgb.at(0)) + ";" +
             std::to_string(rgb.at(1)) + ";" + std::to_string(rgb.at(2));
      break;
  }
}

}  // namespace krow::style
