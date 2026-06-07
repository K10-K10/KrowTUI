#pragma once

#include "core/screen.h"
#include "style/color.h"

namespace __terminal__ {
class DrawObj {
 public:
  void put(int y, int x, const Cell& c, __terminal__::Style style);
};

extern DrawObj drawObj;
}  // namespace __terminal__
