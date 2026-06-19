#include <K10-K10/core/render.h>
#include <K10-K10/core/screen.h>
#include <K10-K10/style/style.h>
#include <K10-K10/utils/base.h>

#include <iostream>
#include <string>

namespace __krow__ {
std::string makeline(const __krow__::Cell& c) {
  if (to_ansi(c.style) == "\033[39;49" && get_flag(c.style) == 0) {
    return c.c.empty() ? " " : c.c;
  }
  std::string line = to_ansi(c.style);
  if ((get_flag(c.style) & StyleFlag::Bold) != 0U) {
    line += ";1";
  }
  if ((get_flag(c.style) & StyleFlag::Dim) != 0U) {
    line += ";2";
  }
  if ((get_flag(c.style) & StyleFlag::Italic) != 0U) {
    line += ";3";
  }
  if ((get_flag(c.style) & StyleFlag::Underline) != 0U) {
    line += ";4";
  }
  if ((get_flag(c.style) & StyleFlag::Blink) != 0U) {
    line += ";5";
  }
  if ((get_flag(c.style) & StyleFlag::RapidBlink) != 0U) {
    line += ";6";
  }
  if ((get_flag(c.style) & StyleFlag::Inverted) != 0U) {
    line += ";7";
  }
  if ((get_flag(c.style) & StyleFlag::Hidden) != 0U) {
    line += ";8";
  }
  if ((get_flag(c.style) & StyleFlag::Strikethrough) != 0U) {
    line += ";9";
  }
  if ((get_flag(c.style) & StyleFlag::DoubleUnderline) != 0U) {
    line += ";21";
  }
  if ((get_flag(c.style) & StyleFlag::Overline) != 0U) {
    line += ";53";
  }

  line += "m" + c.c + "\033[0m";
  return line;
}

void Render::flush() {
  const int W = __krow__::screen.width();
  const int H = __krow__::screen.height();
  std::string line;
  for (int y = 0; y < H; ++y) {
    int start = -1;
    line.clear();
    for (int x = 0; x < W; ++x) {
      const int i = y * W + x;

      if (__krow__::screen.current[i].c != __krow__::screen.next[i].c ||
          __krow__::screen.current[i].style.fg_val !=
              __krow__::screen.next[i].style.fg_val ||
          __krow__::screen.current[i].style.bg_val !=
              __krow__::screen.next[i].style.bg_val ||
          __krow__::screen.current[i].style.flag_ !=
              __krow__::screen.next[i].style.flag_) {
        if (start == -1) {
          start = x;
          line.clear();
        }

        line += makeline(__krow__::screen.next[i]);
        __krow__::screen.current[i] = __krow__::screen.next[i];
      } else if (start != -1) {
        krow::utils::moveTo(y, start);
        std::cout << line;
        start = -1;
        line.clear();
      }
    }
    if (start != -1) {
      krow::utils::moveTo(y, start);
      std::cout << line << std::flush;
      line.clear();
    }
  }
  __krow__::screen.current = __krow__::screen.next;
  __krow__::screen.next.clear();
  std::cout << std::flush;
}

Render render;

}  // namespace __krow__
