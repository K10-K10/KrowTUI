#include <K10-K10/core/drawObj.h>
#include <K10-K10/layout/rect.h>
#include <K10-K10/obj/text.h>

#include <string>

namespace terminal {
Text& Text::position(const Rect& r) {
  rect = r;
  return *this;
}

Text& Text::contents(const std::string& text) {
  text_ = text;
  return *this;
}

std::string Text::contents() const { return text_; }

void Text::draw() {
  int l = rect.x;
  int w = (rect.w == FULL) ? __terminal__::screen.width() : rect.w;
  int t = rect.y;
  int h = (rect.h == FULL) ? __terminal__::screen.height() : rect.h;

  int cnt_x = 0;
  int cnt_y = 0;

  size_t byte_idx = 0;
  while (byte_idx < text_.size() && cnt_y < h) {
    if (text_[byte_idx] == '\n') {
      while (cnt_x < w) {
        __terminal__::Cell blank_cell;
        blank_cell.c = " ";
        blank_cell.style = text_style_;
        __terminal__::drawObj.put(t + cnt_y, l + cnt_x, blank_cell);
        cnt_x++;
      }
      cnt_x = 0;
      cnt_y++;
      byte_idx++;
      continue;
    }

    unsigned char ch = text_[byte_idx];
    size_t char_len = 1;

    if ((ch & 0x80) == 0x00)
      char_len = 1;
    else if ((ch & 0xE0) == 0xC0)
      char_len = 2;
    else if ((ch & 0xF0) == 0xE0)
      char_len = 3;
    else if ((ch & 0xF8) == 0xF0)
      char_len = 4;

    if (byte_idx + char_len > text_.size()) break;

    std::string one_char = text_.substr(byte_idx, char_len);
    int visual_width = (char_len > 1) ? 2 : 1;

    if (cnt_x + visual_width > w) {
      while (cnt_x < w) {
        __terminal__::Cell blank_cell;
        blank_cell.c = " ";
        blank_cell.style = text_style_;
        __terminal__::drawObj.put(t + cnt_y, l + cnt_x, blank_cell);
        cnt_x++;
      }
      cnt_x = 0;
      cnt_y++;
      if (cnt_y >= h) break;
    }

    __terminal__::Cell text_cell;
    text_cell.c = one_char;
    text_cell.style = text_style_;
    __terminal__::drawObj.put(t + cnt_y, l + cnt_x, text_cell);

    cnt_x += visual_width;
    byte_idx += char_len;
  }

  while (cnt_y < h) {
    while (cnt_x < w) {
      __terminal__::Cell blank_cell;
      blank_cell.c = " ";
      blank_cell.style = text_style_;
      __terminal__::drawObj.put(t + cnt_y, l + cnt_x, blank_cell);
      cnt_x++;
    }
    cnt_x = 0;
    cnt_y++;
  }
}

}  // namespace terminal
