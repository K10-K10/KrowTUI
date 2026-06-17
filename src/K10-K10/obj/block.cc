#include <K10-K10/core/drawObj.h>
#include <K10-K10/layout/rect.h>
#include <K10-K10/line/text.h>
#include <K10-K10/obj/block.h>
#include <K10-K10/style/border.h>
#include <K10-K10/utils/string_helper.h>

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

  if (!title_.empty()) {
    for (size_t i = 0; i < title_.contents_.size(); ++i) {
      const auto& row = title_.contents_[i];

      auto draw_alignment = [&](const std::queue<Line>& q,
                                style::alignment align) {
        if (q.empty()) return;

        Line line = q.front();
        int title_len = 0;
        for (const auto& c : line.contents_) {
          title_len += __terminal__::get_visual_width(c.first.text_);
        }
        int start_ =
            __terminal__::calc_alignment(align, {l + 1, r - 1}, title_len);
        for (const auto& l : line.contents_) {
          auto v_chars = __terminal__::split_by_visual_character(l.first.text_);

          for (const auto& vc : v_chars) {
            if (start_ > r - 1) break;
            __terminal__::drawObj.put(t, start_, {vc.c, l.first.style_val});
            start_ += vc.width;
          }
        }
      };

      draw_alignment(row.left, style::alignment::LEFT);
      draw_alignment(row.center, style::alignment::CENTER);
      draw_alignment(row.right, style::alignment::RIGHT);
    }
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
