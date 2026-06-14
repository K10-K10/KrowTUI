#include <K10-K10/core/drawObj.h>
#include <K10-K10/layout/rect.h>
#include <K10-K10/obj/input.h>
#include <K10-K10/style/style.h>

#include <algorithm>
#include <csignal>
#include <string>
#include <vector>

namespace terminal {
char& TextField::RowProxy::operator[](size_t index) {
  if (index >= row_.size()) {
    row_.resize(index + 1, ' ');
  }
  return row_[index];
}

TextField::RowProxy TextField::operator[](size_t index) {
  if (index >= contents_.size()) {
    contents_.resize(index + 1);
  }
  return RowProxy(contents_[index]);
}

TextField& TextField::contents(const std::vector<std::string>& text) {
  std::vector<std::string> new_content;
  std::string line;
  max_length_ = 0;
  for (std::string s : text) {
    for (char c : s) {
      line += c;
      if (c == '\n') {
        new_content.push_back(line);
        max_length_ = std::max(max_length_, int(line.size()));
      }
    }
    line = "";
    new_content.push_back(s);
    max_length_ = std::max(max_length_, int(s.size()));
  }
  contents_ = new_content;
  return *this;
}

TextField& TextField::move_cursor(int x, int y) {
  if (x < 0 || y < 0) return *this;
  if (x > max_length_ || y > contents_.size())
    return *this;
  else {
    cursor_x = x;
    cursor_y = y;
    return *this;
  }
}
void TextField::draw() {
  int l = rect.x;
  int w = (rect.w == FULL) ? __terminal__::screen.width() : rect.w;
  int t = rect.y;
  int h = (rect.h == FULL) ? __terminal__::screen.height() : rect.h;
  int offset_x = std::max(0, cursor_x - w + 1);
  int offset_y = std::max(0, cursor_y - h + 1);
  for (int screen_y = 0; screen_y < h; ++screen_y) {
    int data_y = offset_y + screen_y;
    if (data_y >= contents_.size()) break;

    const std::string& s = contents_[data_y];

    for (int screen_x = 0; screen_x < w; ++screen_x) {
      int data_x = offset_x + screen_x;

      if (data_x >= s.size()) break;

      char c = s[data_x];

      if (data_x == cursor_x && data_y == cursor_y) {
        terminal::style::Style c_s = cursor_style_;
        // c_s.flag |= (1 << 6);
        __terminal__::drawObj.put(t + screen_y, l + screen_x,
                                  {std::string{c}, c_s});
      } else {
        __terminal__::drawObj.put(t + screen_y, l + screen_x,
                                  {std::string{c}, text_style_});
      }
    }
  }
  if (cursor_y >= offset_y && cursor_y < offset_y + h) {
    if (cursor_y < contents_.size() && cursor_x == contents_[cursor_y].size()) {
      int screen_x = cursor_x - offset_x;
      int screen_y = cursor_y - offset_y;
      if (screen_x >= 0 && screen_x < w) {
        __terminal__::drawObj.put(t + screen_y, l + screen_x,
                                  {" ", text_style_});
      }
    }
  }
}
}  // namespace terminal
