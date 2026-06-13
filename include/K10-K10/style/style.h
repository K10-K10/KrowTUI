#ifndef INCLUDE_STYLE_STYLE_H_
#define INCLUDE_STYLE_STYLE_H_

#include <K10-K10/style/color.h>

#include <string>

namespace __terminal__ {
class Render;
}

namespace terminal::style {
struct Style {
  Style& fg(const terminal::style::Color& color) {
    fg_sequence = convert_to_ansi(color, true);
    return *this;
  }

  Style& bg(const terminal::style::Color& color) {
    bg_sequence = convert_to_ansi(color, false);
    return *this;
  }

  Style& flag(unsigned int f) {
    flag_ |= f;
    return *this;
  }

 protected:
  friend class __terminal__::Render;
  std::string to_ansi() const { return fg_sequence + bg_sequence; }

 private:
  std::string fg_sequence = "\033[39m";
  std::string bg_sequence = "\033[49m";
  unsigned int flag_ = 0;

  std::string convert_to_ansi(const terminal::style::Color& color, bool is_fg);
};

inline Style Default() { return Style{}; }
}  // namespace terminal::style

#endif
