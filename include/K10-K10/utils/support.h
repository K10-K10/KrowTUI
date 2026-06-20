#ifndef INCLUDE_UTILS_SUPPORT_H_
#define INCLUDE_UTILS_SUPPORT_H_

#include <K10-K10/core/screen.h>
#include <K10-K10/line/line.h>

#include <queue>

namespace __krow__ {
void fill_screen_rect(int y, int x_start, int width, const std::string& ch,
                      const krow::style::Style& style) {
  for (int i = 0; i < width; ++i) {
    if (x_start + i >= ::__krow__::screen.width()) break;
    ::__krow__::screen.put(y, x_start + i, {ch, style});
  }
}
}  // namespace __krow__
#endif
