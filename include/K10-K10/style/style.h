#ifndef INCLUDE_STYLE_STYLE_H_
#define INCLUDE_STYLE_STYLE_H_

#include <K10-K10/style/color.h>

#include <cstdint>
#include <string>

namespace krow::style {
struct Style;
}

namespace __krow__ {
class Render;
std::string to_ansi(const krow::style::Style& style);
unsigned int get_flag(const krow::style::Style& style);
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

namespace krow::style {
struct Style {
  friend std::string __krow__::to_ansi(const Style& style);
  friend unsigned int __krow__::get_flag(const krow::style::Style& style);

 private:
  std::string convert_to_ansi(const krow::style::Color& color, bool is_fg);

 public:
  Style& fg(const krow::style::Color& color) {
    fg_val = convert_to_ansi(color, true);
    return *this;
  }

  Style& bg(const krow::style::Color& color) {
    bg_val = convert_to_ansi(color, false);
    return *this;
  }

  Style& None() {
    flag_ = __krow__::StyleFlag::None;
    return *this;
  }

  Style& bold() {
    flag_ |= __krow__::StyleFlag::Bold;
    return *this;
  }

  Style& dim() {
    flag_ |= __krow__::StyleFlag::Dim;
    return *this;
  }

  Style& italic() {
    flag_ |= __krow__::StyleFlag::Italic;
    return *this;
  }

  Style& underline() {
    flag_ |= __krow__::StyleFlag::Underline;
    return *this;
  }

  Style& blink() {
    flag_ |= __krow__::StyleFlag::Blink;
    return *this;
  }

  Style& rapidBlink() {
    flag_ |= __krow__::StyleFlag::RapidBlink;
    return *this;
  }

  Style& inverted() {
    flag_ |= __krow__::StyleFlag::Inverted;
    return *this;
  }

  Style& hidden() {
    flag_ |= __krow__::StyleFlag::Hidden;
    return *this;
  }

  Style& strikethrough() {
    flag_ |= __krow__::StyleFlag::Strikethrough;
    return *this;
  }

  Style& doubleUnderline() {
    flag_ |= __krow__::StyleFlag::DoubleUnderline;
    return *this;
  }

  Style& overLine() {
    flag_ |= __krow__::StyleFlag::Overline;
    return *this;
  }
  unsigned int get_flag() const { return flag_; }

 private:
  std::string fg_val = "39";
  std::string bg_val = "49";
  friend class __krow__::Render;
  unsigned int flag_ = 0;
};

inline Style Default() { return Style{}; }
}  // namespace krow::style

namespace __krow__ {
inline std::string to_ansi(const krow::style::Style& style) {
  return "\033[" + style.fg_val + ";" + style.bg_val;
}

inline unsigned int get_flag(const krow::style::Style& style) {
  return style.flag_;
}
}  // namespace __krow__

#endif
