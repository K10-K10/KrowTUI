#ifndef INCLUDE_OBJ_OBJ_H_
#define INCLUDE_OBJ_OBJ_H_

#include <K10-K10/layout/rect.h>
namespace krow {

class Screen;

class Object {
 public:
  explicit Object() = default;
  virtual void draw() = 0;
  virtual Object& position(const Rect rect) {
    rect_ = rect;
    return *this;
  }
  virtual ~Object() = default;

 private:
  Rect rect_ = {0, 0, 0, 0};
};

}  // namespace krow

#endif
