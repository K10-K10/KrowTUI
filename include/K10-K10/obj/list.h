#ifndef INCLUDE_OBJ_LIST_H_
#define INCLUDE_OBJ_LIST_H_

#include <K10-K10/layout/rect.h>
#include <K10-K10/line/text.h>
#include <K10-K10/obj/obj.h>
#include <K10-K10/style/style.h>

#include <string>
#include <vector>

namespace krow {

class List : public Object {
 public:
  explicit List() = default;
  ~List() = default;
  List& position(const Rect& r);
  List& items(std::vector<Text> items);
  const std::vector<Text>& items() const;
  List& add_item(const Text& s);
  List& clear() {
    items_.clear();
    return *this;
  }
  Text selected_item() const;
  void move_up();
  void move_down();
  int selected_index() const;
  void draw() override;

  List& selector_symbol(const std::string& symbol) {
    selector_symbol_ = symbol;
    return *this;
  }

  List& contents_style(const style::Style& s) {
    contents_style_ = s;
    return *this;
  };
  List& selector_style(const style::Style& s) {
    selector_style_ = s;
    return *this;
  };
  List& highlight_style(const style::Style& s) {
    highlight_style_ = s;
    return *this;
  };

 private:
  Rect rect = {0, 0, 0, 0};
  std::vector<Text> items_;
  std::string selector_symbol_ = ">";
  int selected_ = 0;
  int draw_index_num_ = 0;
  krow::style::Style contents_style_, selector_style_, highlight_style_;
};

}  // namespace krow

#endif
