#pragma once

#include <K10-K10/layout/rect.h>
#include <K10-K10/obj/obj.h>
#include <K10-K10/style/color.h>

#include <string>

namespace terminal {

class Text : private Object {
 public:
  Text& position(const Rect& r);
  Text& contents(const std::string& text);
  std::string get_text() const;
  void draw() override;

  Text& bg_color(int bg) {
    style_.bg = bg;
    return *this;
  }
  Text& fg_color(int fg) {
    style_.fg = fg;
    return *this;
  }

 private:
  __terminal__::Style style_;
  Rect rect = {0, 0, 0, 0};
  std::string text_ = "";
};

}  // namespace terminal
