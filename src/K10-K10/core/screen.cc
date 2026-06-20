#include <K10-K10/core/screen.h>

#include <algorithm>
#include <cstddef>
#include <vector>

namespace __krow__ {

int Screen::width() const { return width_; }
int Screen::height() const { return height_; }

void Screen::resize(int w, int h) {
  width_ = w;
  height_ = h;

  const size_t size = static_cast<size_t>(width_) * height_;
  current.assign(size, {" "});
  next.assign(size, {" "});
}

void Screen::clear() { std::fill(next.begin(), next.end(), Cell{" "}); }

void Screen::put(int x, int y, const Cell& c) {
  if (x >= 0 && x < width_ && y >= 0 && y < height_) {
    next[y * width_ + x] = c;
  }
}

__krow__::Screen screen;

}  // namespace __krow__
