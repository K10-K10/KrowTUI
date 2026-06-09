#include "core/render.h"

#include <fstream>
#include <iostream>
#include <string>

#include "core/screen.h"
#include "utils/base.h"

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

std::string makeline(const __terminal__::Cell& c) {
  std::string line =
      "\033[" + std::to_string(c.style.fg) + ";" + std::to_string(c.style.bg);

  if (c.style.flag & StyleFlag::Bold) line += ";1";
  if (c.style.flag & StyleFlag::Dim) line += ";2";
  if (c.style.flag & StyleFlag::Italic) line += ";3";
  if (c.style.flag & StyleFlag::Underline) line += ";4";
  if (c.style.flag & StyleFlag::Blink) line += ";5";
  if (c.style.flag & StyleFlag::RapidBlink) line += ";6";
  if (c.style.flag & StyleFlag::Inverted) line += ";7";
  if (c.style.flag & StyleFlag::Hidden) line += ";8";
  if (c.style.flag & StyleFlag::Strikethrough) line += ";9";
  if (c.style.flag & StyleFlag::DoubleUnderline) line += ";21";
  if (c.style.flag & StyleFlag::Overline) line += ";53";

  line += "m" + c.c + "\033[0m";

  return line;
}

namespace __terminal__ {
void Render::flush() {
  int W = __terminal__::screen.width();
  int H = __terminal__::screen.height();
  int start = -1;
  std::string line;
  for (int y = 0; y < H; ++y) {
    start = -1;
    line.clear();
    for (int x = 0; x < W; ++x) {
      int i = y * W + x;

      if (__terminal__::screen.current[i].c != __terminal__::screen.next[i].c ||
          __terminal__::screen.current[i].style.fg !=
              __terminal__::screen.next[i].style.fg ||
          __terminal__::screen.current[i].style.bg !=
              __terminal__::screen.next[i].style.bg ||
          __terminal__::screen.current[i].style.flag !=
              __terminal__::screen.next[i].style.flag) {
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
      start = -1;
      line.clear();
    }
  }
  __terminal__::screen.current = __terminal__::screen.next;
  __terminal__::screen.next.clear();
  std::cout << std::flush;
}

Render render;

}  // namespace __terminal__
