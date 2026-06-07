#pragma once

#include <string>
#include <vector>

#include "style/color.h"

namespace terminal {
class Object;
}

namespace __terminal__ {
struct Cell {
  std::string c = "";
  int fg = -1, bg = -1;
};

class App;
class Render;
class DrawObj;
class Screen {
  friend App;
  friend Render;
  friend DrawObj;

 public:
  int width() const;
  int height() const;

 private:
  void clear();
  void put(int x, int y, Cell c, __terminal__::Style style);
  void resize(int x, int y);

  std::vector<Cell> current, next;
  int width_, height_;
};
extern __terminal__::Screen screen;

}  // namespace __terminal__
