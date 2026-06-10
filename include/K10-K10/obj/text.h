#pragma once

#include <K10-K10/layout/rect.h>
#include <K10-K10/obj/obj.h>

#include <string>

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
