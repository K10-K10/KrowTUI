#include <K10-K10/style/alignment.h>

#include <utility>

namespace __terminal__ {
int calc_alignment(terminal::style::alignment ali, std::pair<int, int> place,
                   int length) {
  int start_pos = place.first;
  int width = place.second;

  switch (ali) {
    case terminal::style::alignment::LEFT:
      return start_pos;

    case terminal::style::alignment::CENTER:
      return start_pos + (width - length) / 2;

    case terminal::style::alignment::RIGHT:
      return width + start_pos - length;

    default:
      return start_pos;
  }
}

}  // namespace __terminal__
