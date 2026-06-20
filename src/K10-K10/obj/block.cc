#include <K10-K10/core/screen.h>
#include <K10-K10/layout/rect.h>
#include <K10-K10/line/line.h>
#include <K10-K10/line/text.h>
#include <K10-K10/obj/block.h>
#include <K10-K10/style/alignment.h>
#include <K10-K10/style/border.h>
#include <K10-K10/utils/string_helper.h>

#include <cstddef>
#include <queue>

void krow::Block::draw() {
  int l = rect.x;
  const int w = (rect.w == FULL) ? ::__krow__::screen.width() : rect.w;
  int r = l + w - 1;
  int t = rect.y;
  const int h = (rect.h == FULL) ? ::__krow__::screen.height() : rect.h;
  const int b = t + h - 1;
  if (w < 2 || h < 2) {
    return;
  }

  const auto& s = *border_type_;
  const bool has_top =
      (edges_ & krow::style::Borders::TOP) != krow::style::Borders::NONE;
  const bool has_bottom =
      (edges_ & krow::style::Borders::BOTTOM) != krow::style::Borders::NONE;
  const bool has_left =
      (edges_ & krow::style::Borders::LEFT) != krow::style::Borders::NONE;
  const bool has_right =
      (edges_ & krow::style::Borders::RIGHT) != krow::style::Borders::NONE;

  for (int x = l; x <= r; ++x) {
    if (has_top) {
      ::__krow__::screen.put(t, x, {s.h, border_style_});
    }
    if (has_bottom) {
      ::__krow__::screen.put(b, x, {s.h, border_style_});
    }
  }
  for (int y = t; y <= b; ++y) {
    if (has_left) {
      ::__krow__::screen.put(y, l, {s.v, border_style_});
    }
    if (has_right) {
      ::__krow__::screen.put(y, r, {s.v, border_style_});
    }
  }
  if (has_top && has_left) {
    ::__krow__::screen.put(t, l, {s.tl, border_style_});
  }
  if (has_top && has_right) {
    ::__krow__::screen.put(t, r, {s.tr, border_style_});
  }
  if (has_bottom && has_left) {
    ::__krow__::screen.put(b, l, {s.bl, border_style_});
  }
  if (has_bottom && has_right) {
    ::__krow__::screen.put(b, r, {s.br, border_style_});
  }

  if (!title_.empty()) {
    for (size_t i = 0; i < title_.contents_.size(); ++i) {
      const auto& row = title_.contents_[i];
      auto draw_alignment = [&](std::queue<Line> q, style::alignment align) {
        if (q.empty()) {
          return;
        }
        Line merged_line;
        while (!q.empty()) {
          const Line front_line = q.front();
          q.pop();
          for (const auto& item : front_line.contents_) {
            merged_line.contents_.push_back(item);
          }
        }

        int title_len = 0;
        for (const auto& c : merged_line.contents_) {
          title_len += ::__krow__::get_visual_width(c.first.text_);
        }

        const int start_ =
            ::__krow__::calc_alignment(align, {l + 1, r - 1}, title_len);

        merged_line.draw_line({start_, t, (r - 1) - start_ + 1, 1}, align);
      };

      draw_alignment(row.left, style::alignment::LEFT);
      draw_alignment(row.center, style::alignment::CENTER);
      draw_alignment(row.right, style::alignment::RIGHT);
    }

    if (!bottom_title_.empty()) {
      for (size_t i = 0; i < bottom_title_.contents_.size(); ++i) {
        const auto& row = bottom_title_.contents_[i];
        auto draw_alignment = [&](std::queue<Line> q, style::alignment align) {
          if (q.empty()) {
            return;
          }
          Line merged_line;
          while (!q.empty()) {
            const Line front_line = q.front();
            q.pop();
            for (const auto& item : front_line.contents_) {
              merged_line.contents_.push_back(item);
            }
          }

          int title_len = 0;
          for (const auto& c : merged_line.contents_) {
            title_len += ::__krow__::get_visual_width(c.first.text_);
          }

          const int start_ =
              ::__krow__::calc_alignment(align, {l + 1, r - 1}, title_len);

          merged_line.draw_line({start_, b, (r - 1) - start_ + 1, 1}, align);
        };

        draw_alignment(row.left, style::alignment::LEFT);
        draw_alignment(row.center, style::alignment::CENTER);
        draw_alignment(row.right, style::alignment::RIGHT);
      }
    }
  }
}
