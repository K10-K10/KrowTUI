#pragma once

#include <K10-K10/layout/rect.h>
#include <K10-K10/obj/obj.h>
#include <K10-K10/style/color.h>

#include <string>
#include <vector>

namespace terminal {

class List : public Object {
 public:
  List& position(const Rect& r);
  List& items(std::vector<std::string> items);
  const std::vector<std::string>& items() const;
  List& add_item(const std::string& s);
  const std::string selected_item() const;
  void move_up();
  void move_down();
  int selected_index() const;
  void draw() override;

  List& selector(const std::string& symbol) {
    selector_symbol = symbol;
    return *this;
  }
  List& field_color(int bg) {
    style_.bg = bg;
    return *this;
  }
  List& field_color(utils::FillColor bg) {
    style_.bg = static_cast<int>(bg);
    return *this;
  }
  List& text_color(int fg) {
    style_.fg = fg;
    return *this;
  }
  List& text_color(utils::TextColor fg) {
    style_.fg = static_cast<int>(fg);
    return *this;
  }
  List& selector_color(int fg) {
    selector_style_.fg = fg;
    return *this;
  }
  List& selector_color(utils::TextColor fg) {
    selector_style_.fg = static_cast<int>(fg);
    return *this;
  }
  List& highlight_bg(int bg) {
    highlight_style_.bg = bg;
    return *this;
  }
  List& highlight_bg(utils::FillColor bg) {
    highlight_style_.bg = static_cast<int>(bg);
    return *this;
  }
  List& highlight_fg(int fg) {
    highlight_style_.fg = fg;
    return *this;
  }
  List& highlight_fg(utils::TextColor fg) {
    highlight_style_.fg = static_cast<int>(fg);
    return *this;
  }

 private:
  Rect rect = {0, 0, 0, 0};
  std::vector<std::string> items_ = {};
  std::string selector_symbol = ">";
  int selected_ = 0;
  int draw_index_num_ = 0;
  __terminal__::Style style_, highlight_style_, selector_style_;
};

}  // namespace terminal
