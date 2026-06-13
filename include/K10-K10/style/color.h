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

};  // namespace terminal::style

#endif
