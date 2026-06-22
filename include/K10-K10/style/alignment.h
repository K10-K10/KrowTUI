/*
Copyright (c) 2026 K10-K10
SPDX-License-Identifier: MIT
*/

#ifndef INCLUDE_STYLE_ALIGNMENT_H_
#define INCLUDE_STYLE_ALIGNMENT_H_

#include <cstdint>
#include <utility>

namespace krow::style {
enum alignment : uint8_t { LEFT, CENTER, RIGHT };
}

namespace __krow__ {
int calc_alignment(krow::style::alignment ali, std::pair<int, int> place,
                   int length);
}

#endif
