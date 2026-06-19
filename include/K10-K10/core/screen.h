#ifndef INCLUDE_CORE_SCREEN_H_
#define INCLUDE_CORE_SCREEN_H_

#include <K10-K10/style/style.h>

#include <string>
#include <vector>
namespace krow {
class Object;
}

namespace __krow__ {
struct Cell {
  std::string c;
  krow::style::Style style;
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

  std::vector<Cell> current, next;
  int width_ = 0, height_ = 0;
};
extern __krow__::Screen screen;

}  // namespace __krow__

#endif
