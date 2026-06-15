#include <K10-K10/style/alignment.h>

#include <utility>

namespace __terminal__ {
int calc_alignment(terminal::style::alignment ali, std::pair<int, int> place,
                   int length) {
  int start_pos = place.first;
  int end_pos = place.second;
  int total_width = end_pos - start_pos + 1;

  switch (ali) {
    case terminal::style::alignment::LEFT:
      return start_pos;

    case terminal::style::alignment::CENTER:
      return start_pos + (total_width - length) / 2;

    case terminal::style::alignment::RIGHT:
      return end_pos - length + 1;

    default:
      return start_pos;
  }
}

}  // namespace __terminal__
