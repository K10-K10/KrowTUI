#ifndef INCLUDE_STYLE_STYLE_H_
#define INCLUDE_STYLE_STYLE_H_

#include <K10-K10/style/color.h>
#include <K10-K10/style/text_style.h>

#include <string>

namespace terminal::style {
struct Style;
}

namespace __terminal__ {
class Render;
std::string to_ansi(const terminal::style::Style& style);
unsigned int get_flag(const terminal::style::Style& style);
}  // namespace __terminal__

namespace terminal::style {
struct Style {
  friend std::string __terminal__::to_ansi(const Style& style);
  friend unsigned int __terminal__::get_flag(
      const terminal::style::Style& style);

 private:
  std::string convert_to_ansi(const terminal::style::Color& color, bool is_fg);

 public:
  Style& fg(const terminal::style::Color& color) {
    fg_val = convert_to_ansi(color, true);
    return *this;
  }

  Style& bg(const terminal::style::Color& color) {
    bg_val = convert_to_ansi(color, false);
    return *this;
  }

  Style& None() {
    flag_ = __terminal__::StyleFlag::None;
    return *this;
  }

  Style& bold() {
    flag_ |= __terminal__::StyleFlag::Bold;
    return *this;
  }

  Style& dim() {
    flag_ |= __terminal__::StyleFlag::Dim;
    return *this;
  }

  Style& italic() {
    flag_ |= __terminal__::StyleFlag::Italic;
    return *this;
  }

  Style& underline() {
    flag_ |= __terminal__::StyleFlag::Underline;
    return *this;
  }

  Style& blink() {
    flag_ |= __terminal__::StyleFlag::Blink;
    return *this;
  }

  Style& rapidBlink() {
    flag_ |= __terminal__::StyleFlag::RapidBlink;
    return *this;
  }

  Style& inverted() {
    flag_ |= __terminal__::StyleFlag::Inverted;
    return *this;
  }

  Style& hidden() {
    flag_ |= __terminal__::StyleFlag::Hidden;
    return *this;
  }

  Style& strikethrough() {
    flag_ |= __terminal__::StyleFlag::Strikethrough;
    return *this;
  }

  Style& doubleUnderline() {
    flag_ |= __terminal__::StyleFlag::DoubleUnderline;
    return *this;
  }

  Style& overLine() {
    flag_ |= __terminal__::StyleFlag::Overline;
    return *this;
  }
  unsigned int get_flag() const { return flag_; }

 private:
  std::string fg_val = "39";
  std::string bg_val = "49";
  friend class __terminal__::Render;
  unsigned int flag_ = 0;
};

inline Style Default() { return Style{}; }
}  // namespace terminal::style

namespace __terminal__ {
inline std::string to_ansi(const terminal::style::Style& style) {
  return "\033[" + style.fg_val + ";" + style.bg_val;
}

inline unsigned int get_flag(const terminal::style::Style& style) {
  return style.flag_;
}
}  // namespace __terminal__

#endif
