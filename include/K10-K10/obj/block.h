#ifndef INCLUDE_OBJ_BLOCK_H_
#define INCLUDE_OBJ_BLOCK_H_

#include <K10-K10/layout/rect.h>
#include <K10-K10/obj/obj.h>
#include <K10-K10/style/border.h>
#include <K10-K10/style/style.h>

namespace krow {
class Block : public Object {
 private:
 public:
  explicit Block() = default;
  ~Block() = default;
  void draw() override;
  Block& position(const Rect& r);
  Block& border_type(const krow::style::Border& type) {
    border_type_ = &type;
    return *this;
  }
  Block& borders(const krow::style::Borders type_) {
    edges_ = type_;
    return *this;
  }
  Block& border_style(const style::Style& style) {
    border_style_ = style;
    return *this;
  }

 private:
  style::Style border_style_;
  std::string title_, bottom_title_;
  Rect rect = {0, 0, 0, 0};
  const krow::style::Border* border_type_ = &krow::style::SINGLE;
  krow::style::Borders edges_ = krow::style::Borders::ALL;
};

}  // namespace krow

#endif
