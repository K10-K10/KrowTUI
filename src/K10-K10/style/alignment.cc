#include <K10-K10/style/alignment.h>

#include <utility>

namespace __krow__ {
int calc_alignment(krow::style::alignment ali, std::pair<int, int> place,
                   int length) {
  const int start_pos = place.first;
  const int width = place.second;

  switch (ali) {
    case krow::style::alignment::LEFT:
      return start_pos;

    case krow::style::alignment::CENTER:
      return start_pos + (width - length) / 2;

    case krow::style::alignment::RIGHT:
      return width + start_pos - length;

    default:
      return start_pos;
  }
}

}  // namespace __krow__
