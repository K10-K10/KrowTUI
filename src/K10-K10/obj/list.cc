#include <K10-K10/core/drawObj.h>
#include <K10-K10/layout/rect.h>
#include <K10-K10/line/text.h>
#include <K10-K10/obj/list.h>
#include <K10-K10/style/style.h>
#include <K10-K10/utils/string_helper.h>

#include <string>
#include <vector>

namespace krow {
List& List::position(const Rect& r) {
  rect = r;
  return *this;
}

List& List::items(std::vector<Text> items) {
  items_ = std::move(items);
  selected_ = 0;
  return *this;
}

const std::vector<Text>& List::items() const { return items_; }

List& List::add_item(const Text& s) {
  items_.push_back(s);
  return *this;
}

const Text List::selected_item() const {
  if (items_.empty())
    return {""_s};
  else
    return items_[selected_];
}

void List::move_up() {
  if (selected_ > 0) {
    --selected_;
  }

  if (selected_ < draw_index_num_) {
    draw_index_num_ = selected_;
  }
}

void List::move_down() {
  int max_items = static_cast<int>(items_.size());
  if (selected_ + 1 < max_items) {
    ++selected_;
  }

  int view_height = rect.h;

  if (selected_ >= draw_index_num_ + view_height) {
    draw_index_num_ = selected_ - view_height + 1;
  }
}

int List::selected_index() const { return selected_; }

void List::draw() {
  int l = rect.x;
  int w = (rect.w == FULL) ? __krow__::screen.width() : rect.w;
  int t = rect.y;
  int h = (rect.h == FULL) ? __krow__::screen.height() : rect.h;

  if (w < 2 || h < 2) return;
  if (l >= __krow__::screen.width() || t >= __krow__::screen.height()) return;

  if (t + h > __krow__::screen.height()) {
    h = __krow__::screen.height() - t;
  }

  int max_items = items_.size();
  int selector_width = __krow__::get_visual_width(selector_symbol_);
  int max_text_width = w - selector_width;

  for (int i = 0; i < h; ++i) {
    int idx = draw_index_num_ + i;
    int cy = t + i;
    if (cy >= __krow__::screen.height()) break;

    bool has_item = (idx < max_items && idx >= 0);
    bool selected = (has_item && idx == selected_);
    int current_sel_w = 0;
    if (selected) {
      auto sel_chars = __krow__::split_by_visual_character(selector_symbol_);
      for (const auto& vc : sel_chars) {
        if (current_sel_w + vc.width > selector_width) break;

        if (l + current_sel_w >= __krow__::screen.width()) break;

        __krow__::Cell sel_cell;
        sel_cell.c = vc.c;
        sel_cell.style = selector_style_;
        __krow__::drawObj.put(cy, l + current_sel_w, sel_cell);

        current_sel_w += vc.width;
      }
    }

    while (current_sel_w < selector_width) {
      if (l + current_sel_w >= __krow__::screen.width()) break;
      __krow__::Cell blank_sel_cell;
      blank_sel_cell.c = " ";
      blank_sel_cell.style = contents_style_;
      __krow__::drawObj.put(cy, l + current_sel_w, blank_sel_cell);
      current_sel_w++;
    }

    krow::style::Style current_bg_style =
        selected ? highlight_style_ : contents_style_;
    for (int tx = 0; tx < max_text_width; ++tx) {
      if (l + selector_width + tx >= __krow__::screen.width()) break;
      __krow__::Cell bg_cell;
      bg_cell.c = " ";
      bg_cell.style = current_bg_style;
      __krow__::drawObj.put(cy, l + selector_width + tx, bg_cell);
    }
    if (has_item) {
      Text& item_text = items_[idx];

      for (size_t row_idx = 0; row_idx < item_text.contents_.size();
           ++row_idx) {
        const auto& row = item_text.contents_[row_idx];

        auto draw_list_alignment = [&](std::queue<Line> q,
                                       style::alignment align) {
          if (q.empty()) return;

          Line merged_line;
          while (!q.empty()) {
            Line front_line = q.front();
            q.pop();
            for (const auto& item : front_line.contents_) {
              merged_line.contents_.push_back(item);
            }
          }

          int text_len = 0;
          for (const auto& c : merged_line.contents_) {
            text_len += __krow__::get_visual_width(c.first.text_);
          }

          int text_left_bound = l + selector_width;
          int text_right_bound = text_left_bound + max_text_width - 1;

          if (text_right_bound >= __krow__::screen.width()) {
            text_right_bound = __krow__::screen.width() - 1;
          }

          int start_ = __krow__::calc_alignment(
              align, {text_left_bound, text_right_bound}, text_len);

          for (const auto& l_element : merged_line.contents_) {
            auto v_chars =
                __krow__::split_by_visual_character(l_element.first.text_);

            for (const auto& vc : v_chars) {
              if (start_ > text_right_bound ||
                  start_ >= __krow__::screen.width())
                break;
              if (start_ < 0) {
                start_ += vc.width;
                continue;
              }

              __krow__::Cell text_cell;
              text_cell.c = vc.c;
              text_cell.style = l_element.first.style_val;

              __krow__::drawObj.put(cy, start_, text_cell);
              start_ += vc.width;
            }
          }
        };

        draw_list_alignment(row.left, style::alignment::LEFT);
        draw_list_alignment(row.center, style::alignment::CENTER);
        draw_list_alignment(row.right, style::alignment::RIGHT);
      }
    }
  }
}

}  // namespace krow
