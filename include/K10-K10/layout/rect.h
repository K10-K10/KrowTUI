/*
Copyright (c) 2026 K10-K10
SPDX-License-Identifier: MIT
*/

#ifndef INCLUDE_LAYOUT_RECT_H_
#define INCLUDE_LAYOUT_RECT_H_

#define FULL (-1)

namespace krow {
struct Rect {
  int y, x, h, w;

  int right() const { return x + w; }
  int bottom() const { return y + h; }

  bool contains(int px, int py) const {
    return px >= x && px < x + w && py >= y && py < y + h;
  }
};
}  // namespace krow

#endif
