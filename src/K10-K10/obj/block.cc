#include <K10-K10/core/drawObj.h>
#include <K10-K10/layout/rect.h>
#include <K10-K10/obj/block.h>
#include <K10-K10/style/border.h>

namespace krow {
Block& Block::position(const Rect& r) {
  rect = r;
  return *this;
}

void Block::draw() {
  int l = rect.x;
  int w = (rect.w == FULL) ? __krow__::screen.width() : rect.w;
  int r = l + w - 1;
  int t = rect.y;
  int h = (rect.h == FULL) ? __krow__::screen.height() : rect.h;
  int b = t + h - 1;
  if (w < 2 || h < 2) return;
  auto& s = *border_type_;
  bool has_top =
      (edges_ & krow::style::Borders::TOP) != krow::style::Borders::NONE;
  bool has_bottom =
      (edges_ & krow::style::Borders::BOTTOM) != krow::style::Borders::NONE;
  bool has_left =
      (edges_ & krow::style::Borders::LEFT) != krow::style::Borders::NONE;
  bool has_right =
      (edges_ & krow::style::Borders::RIGHT) != krow::style::Borders::NONE;
  for (int x = l; x <= r; ++x) {
    if (has_top) __krow__::drawObj.put(t, x, {s.h, border_style_});
    if (has_bottom) __krow__::drawObj.put(b, x, {s.h, border_style_});
  }

  for (int y = t; y <= b; ++y) {
    if (has_left) __krow__::drawObj.put(y, l, {s.v, border_style_});
    if (has_right) __krow__::drawObj.put(y, r, {s.v, border_style_});
  }
  if (has_top && has_left) __krow__::drawObj.put(t, l, {s.tl, border_style_});

  if (has_top && has_right) __krow__::drawObj.put(t, r, {s.tr, border_style_});

  if (has_bottom && has_left)
    __krow__::drawObj.put(b, l, {s.bl, border_style_});

  if (has_bottom && has_right)
    __krow__::drawObj.put(b, r, {s.br, border_style_});
}

}  // namespace krow
