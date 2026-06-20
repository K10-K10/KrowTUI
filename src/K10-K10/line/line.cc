#include <K10-K10/core/screen.h>
#include <K10-K10/layout/rect.h>
#include <K10-K10/line/line.h>
#include <K10-K10/style/alignment.h>
#include <K10-K10/utils/string_helper.h>

namespace krow {
void Line::draw_line(const Rect& r, style::alignment al) {
  if (contents_.empty()) {
    return;
  }

  int start = r.x;
  int current = start;

  for (const auto& l : contents_) {
    auto v_chars = ::__krow__::split_by_visual_character(l.first.text_);
    for (auto c : v_chars) {
      if (r.x + r.w <= current) {
        return;
      }

      __krow__::screen.put(r.y, current, {c.get_c(), l.first.style_val});
      current += c.get_width();
    }
  }
}

Line Line::merged_queue(std::queue<Line>& q) {
  ::krow::Line merged;
  while (!q.empty()) {
    for (const auto& item : q.front().contents_) {
      merged.contents_.push_back(item);
    }
    q.pop();
  }
  return merged;
}

}  // namespace krow
