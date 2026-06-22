/*
Copyright (c) 2026 K10-K10
SPDX-License-Identifier: MIT
*/

#ifndef INCLUDE_OBJ_OBJ_H_
#define INCLUDE_OBJ_OBJ_H_

namespace krow {

class Screen;

class Object {
 public:
  explicit Object() = default;
  virtual void draw() = 0;
  virtual ~Object() = default;
};

}  // namespace krow

#endif
