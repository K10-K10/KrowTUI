#include "obj/block.h"

#include "core/drawObj.h"
#include "layout/rect.h"

namespace terminal {
Block& Block::position(const Rect& r) {
  rect = r;
  return *this;
}

Block& Block::border_type(const BorderType::Border& type) {
  border_type_ = &type;
  return *this;
}

Block& Block::borders(const Borders::EdgeType type_) {
  edges_ = type_;
  return *this;
}

void Block::draw() {
  int l = rect.x;
  int w = (rect.w == FULL) ? __terminal__::screen.width() : rect.w;
  int r = l + w - 1;
  int t = rect.y;
  int h = (rect.h == FULL) ? __terminal__::screen.height() : rect.h;
  int b = t + h - 1;
  if (w < 2 || h < 2) return;
  auto& s = *border_type_;
  for (int x = l; x <= r; ++x) {
    if (edges_ & Borders::TOP) __terminal__::drawObj.put(t, x, {s.h, style_});
    if (edges_ & Borders::BOTTOM)
      __terminal__::drawObj.put(b, x, {s.h, style_});
  }

  for (int y = t; y <= b; ++y) {
    if (edges_ & Borders::LEFT) __terminal__::drawObj.put(y, l, {s.v, style_});
    if (edges_ & Borders::RIGHT) __terminal__::drawObj.put(y, r, {s.v, style_});
  }
  if ((edges_ & Borders::TOP) && (edges_ & Borders::LEFT))
    __terminal__::drawObj.put(t, l, {s.tl, style_});

  if ((edges_ & Borders::TOP) && (edges_ & Borders::RIGHT))
    __terminal__::drawObj.put(t, r, {s.tr, style_});

  if ((edges_ & Borders::BOTTOM) && (edges_ & Borders::LEFT))
    __terminal__::drawObj.put(b, l, {s.bl, style_});

  if ((edges_ & Borders::BOTTOM) && (edges_ & Borders::RIGHT))
    __terminal__::drawObj.put(b, r, {s.br, style_});
}

}  // namespace terminal
