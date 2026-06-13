#ifndef INCLUDE_STYLE_BORDER_H_
#define INCLUDE_STYLE_BORDER_H_

#include <cstdint>
namespace terminal::style {
struct Border {
  const char* tl;  // top-left
  const char* tr;
  const char* bl;
  const char* br;
  const char* h;  // horizontal
  const char* v;  // vertical
};

inline const Border SINGLE{"┌", "┐", "└", "┘", "─", "│"};
inline const Border ROUNDED{"╭", "╮", "╰", "╯", "─", "│"};
inline const Border BOLD{"┏", "┓", "┗", "┛", "━", "┃"};
inline const Border DOUBLE{"╔", "╗", "╚", "╝", "═", "║"};

enum class Borders : std::uint8_t {
  NONE = 0,
  TOP = 1 << 0,
  BOTTOM = 1 << 1,
  LEFT = 1 << 2,
  RIGHT = 1 << 3,
  ALL = TOP | BOTTOM | LEFT | RIGHT
};
inline Borders operator&(Borders a, Borders b) {
  return static_cast<Borders>(static_cast<std::uint8_t>(a) &
                              static_cast<std::uint8_t>(b));
}

inline Borders operator|(Borders a, Borders b) {
  return static_cast<Borders>(static_cast<std::uint8_t>(a) |
                              static_cast<std::uint8_t>(b));
}

}  // namespace terminal::style

#endif
