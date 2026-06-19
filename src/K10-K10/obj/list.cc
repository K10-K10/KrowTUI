#include <K10-K10/core/drawObj.h>
#include <K10-K10/layout/rect.h>
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

List& List::items(std::vector<std::string> items) {
  items_ = std::move(items);
  selected_ = 0;
  return *this;
}

const std::vector<std::string>& List::items() const { return items_; }

List& List::add_item(const std::string& s) {
  items_.push_back(s);
  return *this;
}

const std::string List::selected_item() const {
  if (items_.empty())
    return "";
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

  int max_items = items_.size();

  int selector_width = __krow__::get_visual_width(selector_symbol_);

  for (int i = 0; i < h; ++i) {
    int idx = draw_index_num_ + i;
    int cy = t + i;

    bool has_item = (idx < max_items);
    bool selected = (has_item && idx == selected_);

    krow::style::Style current_text_style =
        selected ? highlight_style_ : contents_style_;

    int current_sel_w = 0;

    if (selected) {
      auto sel_chars = __krow__::split_by_visual_character(selector_symbol_);
      for (const auto& vc : sel_chars) {
        if (current_sel_w + vc.width > selector_width) break;

        __krow__::Cell sel_cell;
        sel_cell.c = vc.c;
        sel_cell.style = selector_style_;
        __krow__::drawObj.put(cy, l + current_sel_w, sel_cell);

        current_sel_w += vc.width;
      }
    }

    while (current_sel_w < selector_width) {
      __krow__::Cell blank_sel_cell;
      blank_sel_cell.c = " ";
      blank_sel_cell.style = contents_style_;
      __krow__::drawObj.put(cy, l + current_sel_w, blank_sel_cell);
      current_sel_w++;
    }

    int max_text_width = w - selector_width;
    int current_text_w = 0;
    const std::string& text = has_item ? items_[idx] : "";

    if (has_item) {
      auto text_chars = __krow__::split_by_visual_character(text);
      for (const auto& vc : text_chars) {
        if (current_text_w + vc.width > max_text_width) break;

        __krow__::Cell text_cell;
        text_cell.c = vc.c;
        text_cell.style = current_text_style;
        __krow__::drawObj.put(cy, l + selector_width + current_text_w,
                              text_cell);

        current_text_w += vc.width;
      }
    }

    while (current_text_w < max_text_width) {
      __krow__::Cell bg_cell;
      bg_cell.c = " ";
      bg_cell.style = contents_style_;
      __krow__::drawObj.put(cy, l + selector_width + current_text_w, bg_cell);
      current_text_w++;
    }
  }
}

}  // namespace krow
