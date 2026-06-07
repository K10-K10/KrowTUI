#include "core/drawObj.h"

#include "core/screen.h"
#include "style/color.h"
namespace __terminal__ {
void DrawObj::put(int y, int x, const Cell& c, __terminal__::Style style) {
  __terminal__::screen.put(x, y, c, style);
  return;
}

DrawObj drawObj;

}  // namespace __terminal__
