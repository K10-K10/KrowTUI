#pragma once

#include <string>
#include <vector>

#include "layout/rect.h"
#include "obj/obj.h"

namespace terminal {
class TextField : private Object {
 public:
  TextField& position(const Rect& r) {
    rect = r;
    return *this;
  }
  TextField& contents(const std::vector<std::string>& text);
  std::vector<std::string> get_contents() const { return contents_; }
  TextField& move_cursor(int x, int y);
  TextField& insert_char(char c);
  TextField& delete_char();

  void draw() override;
  class RowProxy {
    std::string& row_;

   public:
    RowProxy(std::string& row) : row_(row) {}
    char& operator[](size_t index);
    operator std::string&() { return row_; }
    operator const std::string&() const { return row_; }
  };
  RowProxy operator[](size_t index);

  const std::string& operator[](size_t index) const {
    return contents_.at(index);
  }

 private:
  Rect rect;
  std::vector<std::string> contents_;
  int max_length_;
  int cursor_x = 0, cursor_y = 0;
};
}  // namespace terminal
