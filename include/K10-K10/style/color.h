#ifndef INCLUDE_STYLE_COLOR_H_
#define INCLUDE_STYLE_COLOR_H_

#include <string>

namespace terminal::style {

enum class BasicColor {
  Default,
  Black,
  Red,
  Green,
  Yellow,
  Blue,
  Magenta,
  Cyan,
  White
};

struct Color {
  enum class Type { Basic, Extended256, RGB };

  Type type = Type::Basic;
  BasicColor basic = BasicColor::Default;
  int code256 = 0;
  int r = 0, g = 0, b = 0;
  Color() : type(Type::Basic), basic(BasicColor::Default) {}
  Color(BasicColor bc) : type(Type::Basic), basic(bc) {}

  Color(int code) : type(Type::Extended256), code256(code) {}

  Color(int r, int g, int b) : type(Type::RGB), r(r), g(g), b(b) {}
};

}  // namespace terminal::style

namespace __terminal__ {

struct Style {
  Style& fg(const terminal::utils::Color& color) {
    fg_sequence = convert_to_ansi(color, true);
    return *this;
  }

  Style& bg(const terminal::utils::Color& color) {
    bg_sequence = convert_to_ansi(color, false);
    return *this;
  }

  std::string fg_sequence = "\033[39m";
  std::string bg_sequence = "\033[49m";
  unsigned int flag = 0;

 private:
  std::string convert_to_ansi(const terminal::utils::Color& color, bool is_fg) {
    int base = is_fg ? 30 : 40;
    int ext = is_fg ? 38 : 48;

    if (color.type == terminal::utils::Color::Type::Basic) {
      if (color.basic == terminal::utils::BasicColor::Default) {
        return "\033[" + std::to_string(base + 9) + "m";  // 39m or 49m
      }
      return "\033[" +
             std::to_string(base + static_cast<int>(color.basic) - 1) + "m";
    } else if (color.type == terminal::utils::Color::Type::Extended256) {
      return "\033[" + std::to_string(ext) + ";5;" +
             std::to_string(color.code256) + "m";
    } else {
      return "\033[" + std::to_string(ext) + ";2;" + std::to_string(color.r) +
             ";" + std::to_string(color.g) + ";" + std::to_string(color.b) +
             "m";
    }
  }
};

}  // namespace __terminal__

#endif
