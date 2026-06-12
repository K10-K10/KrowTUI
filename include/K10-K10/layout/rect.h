#ifndef INCLUDE_LAYOUT_RECT_H_
#define INCLUDE_LAYOUT_RECT_H_

#define FULL -1

namespace terminal {
struct Rect {
  int x, y, w, h;

  int right() const { return x + w; }
  int bottom() const { return y + h; }

  bool contains(int px, int py) const {
    return px >= x && px < x + w && py >= y && py < y + h;
  }
};
}  // namespace terminal

#endif
