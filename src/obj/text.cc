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

std::string Text::get_text() { return text_; }

void Text::draw() {
  // Implementation for drawing text
  int cnt_x = 0;
  int cnt_y = 0;

  int l = rect.x;
  int w = (rect.w == FULL) ? __terminal__::screen.width() : rect.w;
  int t = rect.y;
  int h = (rect.h == FULL) ? __terminal__::screen.height() : rect.h;

  for (char c : text_) {
    if (c == '\n') {
      if (w - cnt_x > 0) {
        for (int j = l + cnt_x; j <= w; ++j) {
          __terminal__::drawObj.put(t + cnt_y, l + cnt_x, {" "});
        }
      } else {
        cnt_x = 0;
        ++cnt_y;
      }
    } else {
      __terminal__::drawObj.put(t + cnt_y, l + cnt_x, {std::string{c}});
      ++cnt_x;
      if (cnt_x >= w) {
        cnt_x = 0;
        ++cnt_y;
      }
    }
  }
  return;
}

}  // namespace terminal
