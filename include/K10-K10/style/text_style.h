#ifndef INCLUDE_STYLE_TEXT_STYLE_H_
#define INCLUDE_STYLE_TEXT_STYLE_H_

#include <cstdint>

namespace __krow__ {
enum StyleFlag : std::uint16_t {
  None = 0,
  Bold = 1 << 0,
  Dim = 1 << 1,
  Italic = 1 << 2,
  Underline = 1 << 3,
  Blink = 1 << 4,
  RapidBlink = 1 << 5,
  Inverted = 1 << 6,
  Hidden = 1 << 7,
  Strikethrough = 1 << 8,
  DoubleUnderline = 1 << 9,
  Overline = 1 << 10
};
}  // namespace __krow__

#endif
