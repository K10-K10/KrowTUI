#pragma once

#include <K10-K10/core/screen.h>

namespace __terminal__ {
class DrawObj {
 public:
  explicit DrawObj() = default;
  ~DrawObj() = default;
  static void put(int y, int x, const Cell& c);
};

extern DrawObj drawObj;
}  // namespace __terminal__
