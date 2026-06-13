#ifndef INCLUDE_OBJ_BLOCK_H_
#define INCLUDE_OBJ_BLOCK_H_

#include <K10-K10/layout/rect.h>
#include <K10-K10/obj/obj.h>
#include <K10-K10/style/border.h>
#include <K10-K10/style/color.h>

namespace terminal {
class Block : public Object {
 private:
 public:
  explicit Block() = default;
  ~Block() = default;
  void draw() override;
  Block& position(const Rect& r);
  Block& border_type(const terminal::style::Border& type);
  Block& borders(const terminal::style::EdgeType type_);
  Block& border_color(int bc) {
    style_.fg = bc;
    return *this;
  }
  Block& border_color(terminal::style::TextColor bc) {
    style_.fg = static_cast<int>(bc);
    return *this;
  }

  Block& field_color(int bg) {
    style_.bg = bg;
    return *this;
  }

  Block& field_color(terminal::style::FillColor bg) {
    style_.bg = static_cast<int>(bg);
    return *this;
  }

 private:
  __terminal__::Style style_;
  Rect rect = {0, 0, 0, 0};
  const terminal::style::Border* border_type_ = &terminal::style::SINGLE;
  terminal::style::EdgeType edges_ = terminal::style::ALL;
};

}  // namespace terminal

#endif
