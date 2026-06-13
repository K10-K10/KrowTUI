#include <K10-K10/utils/string_helper.h>

namespace __terminal__ {

int get_visual_width(const std::string& str) {
  int width = 0;
  for (const auto& vc : split_by_visual_character(str)) {
    width += vc.width;
  }
  return width;
}

std::vector<VisualChar> split_by_visual_character(const std::string& str) {
  std::vector<VisualChar> result;
  size_t b_idx = 0;

  while (b_idx < str.size()) {
    unsigned char ch = str[b_idx];
    size_t len = 1;

    if ((ch & 0x80) == 0x00)
      len = 1;
    else if ((ch & 0xE0) == 0xC0)
      len = 2;
    else if ((ch & 0xF0) == 0xE0)
      len = 3;
    else if ((ch & 0xF8) == 0xF0)
      len = 4;

    if (b_idx + len > str.size()) break;

    VisualChar vc;
    vc.c = str.substr(b_idx, len);
    vc.width = (len > 1) ? 2 : 1;

    result.push_back(vc);
    b_idx += len;
  }

  return result;
}

}  // namespace __terminal__
