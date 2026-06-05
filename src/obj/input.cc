#include "obj/input.h"

#include <algorithm>
#include <csignal>
#include <string>
#include <vector>

#include "core/drawObj.h"
#include "layout/rect.h"

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

  for (std::string s : contents_) {
    for (char c : s) {
      __terminal__::drawObj.put(t + cnt_y, l + cnt_x, {std::string{c}});
      ++cnt_x;
      if (cnt_x + l > w) {
        break;
      }
    }
    ++cnt_y;
    if (cnt_y + t > h) return;
    cnt_x = 0;
  }
  return;
}

}  // namespace terminal
