#pragma once

#include <K10-K10/layout/border.h>
#include <K10-K10/layout/rect.h>
#include <K10-K10/obj/obj.h>
#include <K10-K10/style/color.h>

namespace terminal {
class Block : public Object {
 private:
 public:
  void draw() override;
  Block& position(const Rect& r);
  Block& border_type(const BorderType::Border& type);
  Block& borders(const Borders::EdgeType type_);
  Block& border_color(int bc) {
    style_.fg = bc;
    return *this;
  }
  Block& border_color(utils::TextColor bc) {
    style_.fg = static_cast<int>(bc);
    return *this;
  }

  Block& field_color(int bg) {
    style_.bg = bg;
    return *this;
  }

  Block& field_color(utils::FillColor bg) {
    style_.bg = static_cast<int>(bg);
    return *this;
  }

 private:
  __terminal__::Style style_;
  Rect rect = {0, 0, 0, 0};
  const BorderType::Border* border_type_ = &BorderType::SINGLE;
  Borders::EdgeType edges_ = Borders::ALL;
};

}  // namespace terminal
