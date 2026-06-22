/*
Copyright (c) 2026 K10-K10
SPDX-License-Identifier: MIT
*/

#ifndef INCLUDE_CORE_DRAWOBJ_H_
#define INCLUDE_CORE_DRAWOBJ_H_

#include <K10-K10/core/screen.h>

namespace __krow__ {
class DrawObj {
 public:
  explicit DrawObj() = default;
  ~DrawObj() = default;
  static void put(int y, int x, const Cell& c);
};

extern DrawObj drawObj;
}  // namespace __krow__
#endif
