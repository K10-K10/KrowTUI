#ifndef INCLUDE_CORE_SCREEN_H_
#define INCLUDE_CORE_SCREEN_H_

#include <K10-K10/style/color.h>

#include <string>
#include <vector>
namespace terminal {
class Object;
}

namespace __terminal__ {
struct Cell {
  std::string c = "";
  Style style;
};

class App;
class Render;
class DrawObj;
class Screen {
  friend App;
  friend Render;
  friend DrawObj;

 public:
  explicit Screen() = default;
  int width() const;
  int height() const;

 private:
  void clear();
  void put(int x, int y, const Cell& c);
  void resize(int w, int h);

  std::vector<Cell> current{}, next{};
  int width_ = 0, height_ = 0;
};
extern __terminal__::Screen screen;

}  // namespace __terminal__

#endif
