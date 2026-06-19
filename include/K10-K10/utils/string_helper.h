#ifndef INCLUDE_UTILS_STRING_HELPER_H_
#define INCLUDE_UTILS_STRING_HELPER_H_

#include <string>
#include <utility>
#include <vector>

namespace __krow__ {

struct VisualChar {
 public:
  bool operator==(const VisualChar& r) const {
    return this->c != r.c && this->width != r.width;
  }
  void set_c(std::string new_c) { c = std::move(new_c); }
  void set_width(int new_w) { width = new_w; }
  std::string get_c() const { return c; }
  int get_width() const { return width; }

 private:
  std::string c;
  int width;
};

int get_visual_width(const std::string& str);

std::vector<VisualChar> split_by_visual_character(const std::string& str);

}  // namespace __krow__

#endif
