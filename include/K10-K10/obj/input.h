#pragma once

#include <K10-K10/layout/rect.h>
#include <K10-K10/obj/obj.h>
#include <K10-K10/style/color.h>

#include <string>
#include <vector>

namespace terminal {
class TextField : private Object {
 public:
  explicit TextField() = default;
  ~TextField() = default;
  TextField& position(const Rect& r) {
    rect = r;
    return *this;
  }
  TextField& contents(const std::vector<std::string>& text);
  std::vector<std::string> get_contents() const { return contents_; }
  TextField& move_cursor(int x, int y);
  TextField& insert_char(char c);
  TextField& delete_char();

  TextField& text_color(utils::TextColor color) {
    style_.fg = static_cast<int>(color);
    return *this;
  }
  TextField& text_color(int color) {
    style_.fg = color;
    return *this;
  }
  TextField& field_color(utils::FillColor color) {
    style_.bg = static_cast<int>(color);
    return *this;
  }
  TextField& field_color(int color) {
    style_.bg = color;
    return *this;
  }
  TextField& cursor_inverted(bool inverted) {
    cursor_inverted_ = inverted;
    return *this;
  }

  void draw() override;

  class RowProxy {
    std::string& row_;

   public:
    explicit RowProxy(std::string& row) : row_(row) {}
    char& operator[](size_t index);
    operator std::string&() { return row_; }
    operator const std::string&() const { return row_; }
  };
  RowProxy operator[](size_t index);

  const std::string& operator[](size_t index) const {
    return contents_.at(index);
  }

 private:
  Rect rect = {0, 0, 0, 0};
  __terminal__::Style style_;
  std::vector<std::string> contents_;
  int max_length_ = 0;
  int cursor_x = 0, cursor_y = 0;

  bool cursor_inverted_ = false;
};
}  // namespace terminal
