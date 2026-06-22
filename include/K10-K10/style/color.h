/*
Copyright (c) 2026 K10-K10
SPDX-License-Identifier: MIT
*/

#ifndef INCLUDE_STYLE_COLOR_H_
#define INCLUDE_STYLE_COLOR_H_

#include <array>
#include <cstdint>

namespace krow::style {

enum class BasicColor : uint8_t {
  Default,
  Black,
  Red,
  Green,
  Yellow,
  Blue,
  Magenta,
  Cyan,
  White
};

struct Color {
  enum class Type : uint8_t { Basic, Extended256, RGB };

 public:
  Type get_type() const { return type; }
  int get_code256() const { return code256; }
  std::array<int, 3> get_rgb() const { return {r, g, b}; }
  BasicColor get_basic() const { return basic; }
  Color() : type(Type::Basic), basic(BasicColor::Default) {}
  Color(BasicColor bc) : type(Type::Basic), basic(bc) {}

  Color(int code) : type(Type::Extended256), code256(code) {}

  Color(int r, int g, int b) : type(Type::RGB), r(r), g(g), b(b) {}

 private:
  Type type = Type::Basic;
  int code256 = 0;
  int r = 0, g = 0, b = 0;
  BasicColor basic = BasicColor::Default;
};

};  // namespace krow::style

#endif
