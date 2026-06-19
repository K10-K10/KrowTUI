#ifndef INCLUDE_UTILS_STRING_HELPER_H_
#define INCLUDE_UTILS_STRING_HELPER_H_

#include <string>
#include <vector>

namespace __krow__ {

struct VisualChar {
  std::string c;
  int width;
  bool operator==(const VisualChar&) const = default;
};

int get_visual_width(const std::string& str);

std::vector<VisualChar> split_by_visual_character(const std::string& str);

}  // namespace __krow__

#endif
