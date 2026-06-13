#include <K10-K10/core/drawObj.h>
#include <K10-K10/layout/rect.h>
#include <K10-K10/obj/list.h>
#include <K10-K10/style/style.h>

#include <string>
#include <vector>

namespace terminal {
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
  int w = (rect.w == FULL) ? __terminal__::screen.width() : rect.w;
  int t = rect.y;
  int h = (rect.h == FULL) ? __terminal__::screen.height() : rect.h;
  if (w < 2 || h < 2) return;

  int max_items = items_.size();

  int selector_width = 0;
  {
    size_t b_idx = 0;
    while (b_idx < selector_symbol_.size()) {
      unsigned char ch = selector_symbol_[b_idx];
      size_t len = 1;
      if ((ch & 0x80) == 0x00)
        len = 1;
      else if ((ch & 0xE0) == 0xC0)
        len = 2;
      else if ((ch & 0xF0) == 0xE0)
        len = 3;
      else if ((ch & 0xF8) == 0xF0)
        len = 4;

      if (b_idx + len > selector_symbol_.size()) break;

      selector_width += (len > 1) ? 2 : 1;
      b_idx += len;
    }
  }

  for (int i = 0; i < h; ++i) {
    int idx = draw_index_num_ + i;
    int cy = t + i;

    bool has_item = (idx < max_items);
    bool selected = (has_item && idx == selected_);

    terminal::style::Style current_text_style =
        selected ? highlight_style_ : contents_style_;

    int current_sel_w = 0;

    if (selected) {
      size_t sel_byte_idx = 0;
      while (sel_byte_idx < selector_symbol_.size() &&
             current_sel_w < selector_width) {
        unsigned char ch = selector_symbol_[sel_byte_idx];
        size_t len = 1;
        if ((ch & 0x80) == 0x00)
          len = 1;
        else if ((ch & 0xE0) == 0xC0)
          len = 2;
        else if ((ch & 0xF0) == 0xE0)
          len = 3;
        else if ((ch & 0xF8) == 0xF0)
          len = 4;

        if (sel_byte_idx + len > selector_symbol_.size()) break;

        int vis_w = (len > 1) ? 2 : 1;
        if (current_sel_w + vis_w > selector_width) break;

        __terminal__::Cell sel_cell;
        sel_cell.c = selector_symbol_.substr(sel_byte_idx, len);
        sel_cell.style = selector_style_;
        __terminal__::drawObj.put(cy, l + current_sel_w, sel_cell);

        current_sel_w += vis_w;
        sel_byte_idx += len;
      }
    }

    while (current_sel_w < selector_width) {
      __terminal__::Cell blank_sel_cell;
      blank_sel_cell.c = " ";
      blank_sel_cell.style = contents_style_;
      __terminal__::drawObj.put(cy, l + current_sel_w, blank_sel_cell);
      current_sel_w++;
    }

    int max_text_width = w - selector_width;
    int current_text_w = 0;
    const std::string& text = has_item ? items_[idx] : "";

    if (has_item) {
      size_t text_byte_idx = 0;
      while (text_byte_idx < text.size() && current_text_w < max_text_width) {
        unsigned char ch = text[text_byte_idx];
        size_t len = 1;
        if ((ch & 0x80) == 0x00)
          len = 1;
        else if ((ch & 0xE0) == 0xC0)
          len = 2;
        else if ((ch & 0xF0) == 0xE0)
          len = 3;
        else if ((ch & 0xF8) == 0xF0)
          len = 4;

        if (text_byte_idx + len > text.size()) break;

        int vis_w = (len > 1) ? 2 : 1;
        if (current_text_w + vis_w > max_text_width) break;

        __terminal__::Cell text_cell;
        text_cell.c = text.substr(text_byte_idx, len);
        text_cell.style = current_text_style;
        __terminal__::drawObj.put(cy, l + selector_width + current_text_w,
                                  text_cell);

        current_text_w += vis_w;
        text_byte_idx += len;
      }
    }

    while (current_text_w < max_text_width) {
      __terminal__::Cell bg_cell;
      bg_cell.c = " ";
      bg_cell.style = contents_style_;
      __terminal__::drawObj.put(cy, l + selector_width + current_text_w,
                                bg_cell);
      current_text_w++;
    }
  }
}

}  // namespace terminal
