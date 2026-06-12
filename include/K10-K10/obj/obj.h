#ifndef INCLUDE_OBJ_OBJ_H_
#define INCLUDE_OBJ_OBJ_H_

namespace terminal {

class Screen;

class Object {
 public:
  explicit Object() = default;
  virtual void draw() = 0;
  virtual ~Object() = default;
};

}  // namespace terminal

#endif
