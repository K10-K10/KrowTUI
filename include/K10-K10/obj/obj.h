#pragma once

namespace terminal {

class Screen;

class Object {
 public:
  explicit Object() = default;
  virtual void draw() = 0;
  virtual ~Object() = default;
};

}  // namespace terminal
