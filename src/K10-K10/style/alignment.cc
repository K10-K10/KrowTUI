#include <K10-K10/style/alignment.h>

#include <utility>

namespace __terminal__ {
int calc_alignment(terminal::style::alignment ali, std::pair<int, int> place,
                   int length) {
  switch (ali) {
    case terminal::style::alignment::left:
      return place.first;
      break;
    case terminal::style::alignment::center:
      return (length / 2) - (place.second / 2) + place.first - 1;
      break;
    case terminal::style::alignment::right:
      return place.second - length + place.first;
      break;
    default:
      return -1;
      break;
  }
}

}  // namespace __terminal__
