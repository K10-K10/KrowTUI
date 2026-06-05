#pragma once

#include <string>

#include "layout/rect.h"
#include "obj/obj.h"

namespace terminal {

class Text : private Object {
 public:
  Text& position(const Rect& r);
  Text& contents(const std::string& text);
  std::string get_text();
  void draw() override;

 private:
  Rect rect;
  std::string text_;
};

}  // namespace terminal
