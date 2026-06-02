#include "obj/input.h"

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

void TextField::draw() {
  int cnt_x = 0;
  int cnt_y = 0;

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
