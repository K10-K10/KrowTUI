#include <K10-K10/core/render.h>
#include <K10-K10/core/screen.h>
#include <K10-K10/style/text_style.h>
#include <K10-K10/utils/base.h>

#include <fstream>
#include <iostream>
#include <string>

namespace __terminal__ {
std::string makeline(const __terminal__::Cell& c) {
  if (to_ansi(c.style) == "\033[39;49" && get_flag(c.style) == 0) {
    return c.c.empty() ? " " : c.c;
  }
  std::string line = to_ansi(c.style);
  if (get_flag(c.style) & StyleFlag::Bold) line += ";1";
  if (get_flag(c.style) & StyleFlag::Dim) line += ";2";
  if (get_flag(c.style) & StyleFlag::Italic) line += ";3";
  if (get_flag(c.style) & StyleFlag::Underline) line += ";4";
  if (get_flag(c.style) & StyleFlag::Blink) line += ";5";
  if (get_flag(c.style) & StyleFlag::RapidBlink) line += ";6";
  if (get_flag(c.style) & StyleFlag::Inverted) line += ";7";
  if (get_flag(c.style) & StyleFlag::Hidden) line += ";8";
  if (get_flag(c.style) & StyleFlag::Strikethrough) line += ";9";
  if (get_flag(c.style) & StyleFlag::DoubleUnderline) line += ";21";
  if (get_flag(c.style) & StyleFlag::Overline) line += ";53";

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
          __terminal__::screen.current[i].style.fg_val !=
              __terminal__::screen.next[i].style.fg_val ||
          __terminal__::screen.current[i].style.bg_val !=
              __terminal__::screen.next[i].style.bg_val ||
          __terminal__::screen.current[i].style.flag_ !=
              __terminal__::screen.next[i].style.flag_) {
        if (start == -1) {
          start = x;
          line.clear();
        }

        line += makeline(__terminal__::screen.next[i]);
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
