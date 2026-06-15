#ifndef INCLUDE_STYLE_ALIGNMENT_H_
#define INCLUDE_STYLE_ALIGNMENT_H_

#include <cstdint>
#include <utility>

namespace terminal::style {
enum alignment : uint8_t { left, center, right };
}

namespace __terminal__ {
int calc_alignment(terminal::style::alignment ali, std::pair<int, int> place,
                   int length);
}

#endif
