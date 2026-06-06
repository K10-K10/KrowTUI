#pragma once

namespace terminal::utils {
// text
enum class TextColor {
  Default = 39,
  Black = 30,
  Red = 31,
  Green = 32,
  Yellow = 33,
  Blue = 34,
  Magenta = 35,
  Cyan = 36,
  White = 37
};
// fill
enum class FillColor {
  Default = 49,
  Black = 40,
  Red = 41,
  Green = 42,
  Yellow = 43,
  Blue = 44,
  Magenta = 45,
  Cyan = 46,
  White = 47
};

struct Style {
  TextColor fg = TextColor::Default;
  FillColor bg = FillColor::Default;
  bool bold = false;
  bool inverted = false;
  bool underline = false;
};

int printColor(int txt_color, const char* str);
int printColor(int txt_color, int color, const char* str);

}  // namespace terminal::utils
