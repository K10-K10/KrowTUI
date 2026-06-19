#ifndef INCLUDE_OBJ_INPUT_H_
#define INCLUDE_OBJ_INPUT_H_

#include <K10-K10/layout/rect.h>
#include <K10-K10/line/text.h>
#include <K10-K10/obj/obj.h>
#include <K10-K10/style/style.h>

#include <cstddef>
#include <string>
#include <vector>

namespace krow {
class TextField : private Object {
 public:
  explicit TextField() = default;
  ~TextField() = default;
  TextField& position(const Rect& r) {
    rect = r;
    return *this;
  }

  TextField& contents(const std::vector<Text>& text);
  std::vector<Text> get_contents() const { return contents_; }

  TextField& move_cursor(int x, int y);
  TextField& insert_char(const std::string& c);
  TextField& delete_char();

  TextField& text_style(const style::Style& s) {
    text_style_ = s;
    return *this;
  }

  TextField& cursor_style(const style::Style& s) {
    cursor_style_ = s;
    return *this;
  }

  void draw() override;

  Text& operator[](size_t index);
  const Text& operator[](size_t index) const { return contents_.at(index); }

 private:
  Rect rect = {0, 0, 0, 0};
  krow::style::Style text_style_, cursor_style_;
  std::vector<Text> contents_;
  int max_length_ = 0;
  int cursor_x = 0, cursor_y = 0;

  bool cursor_inverted_ = false;
};
}  // namespace krow

#endif
