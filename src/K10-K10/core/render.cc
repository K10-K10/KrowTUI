#include <K10-K10/core/render.h>
#include <K10-K10/core/screen.h>
#include <K10-K10/utils/base.h>

#include <fstream>
#include <iostream>
#include <string>

enum StyleFlag : unsigned int {
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

namespace __terminal__ {
std::string Render::makeline(const __terminal__::Cell& c) {
  std::string line = c.style.to_ansi();
  if (c.style.flag_ & StyleFlag::Bold) line += ";1";
  if (c.style.flag_ & StyleFlag::Dim) line += ";2";
  if (c.style.flag_ & StyleFlag::Italic) line += ";3";
  if (c.style.flag_ & StyleFlag::Underline) line += ";4";
  if (c.style.flag_ & StyleFlag::Blink) line += ";5";
  if (c.style.flag_ & StyleFlag::RapidBlink) line += ";6";
  if (c.style.flag_ & StyleFlag::Inverted) line += ";7";
  if (c.style.flag_ & StyleFlag::Hidden) line += ";8";
  if (c.style.flag_ & StyleFlag::Strikethrough) line += ";9";
  if (c.style.flag_ & StyleFlag::DoubleUnderline) line += ";21";
  if (c.style.flag_ & StyleFlag::Overline) line += ";53";

  line += "m" + c.c + "\033[0m";

  return line;
}
void Render::flush() {
  int W = __terminal__::screen.width();
  int H = __terminal__::screen.height();
  std::string line;
  for (int y = 0; y < H; ++y) {
    int start = -1;
    line.clear();
    for (int x = 0; x < W; ++x) {
      int i = y * W + x;

      if (__terminal__::screen.current[i].c != __terminal__::screen.next[i].c ||
          __terminal__::screen.current[i].style.fg_sequence !=
              __terminal__::screen.next[i].style.fg_sequence ||
          __terminal__::screen.current[i].style.bg_sequence !=
              __terminal__::screen.next[i].style.bg_sequence ||
          __terminal__::screen.current[i].style.flag_ !=
              __terminal__::screen.next[i].style.flag_) {
        if (start == -1) {
          start = x;
          line.clear();
        }

        line += __terminal__::screen.next[i].style.to_ansi() +
                __terminal__::screen.next[i].c + "\033[0m";
        __terminal__::screen.current[i] = __terminal__::screen.next[i];
      } else if (start != -1) {
        terminal::utils::moveTo(y, start);
        std::cout << line;
        start = -1;
        line.clear();
      }
    }
    if (start != -1) {
      terminal::utils::moveTo(y, start);
      std::cout << line << std::flush;
      line.clear();
    }
  }
  __terminal__::screen.current = __terminal__::screen.next;
  __terminal__::screen.next.clear();
  std::cout << std::flush;
}

Render render;

}  // namespace __terminal__
