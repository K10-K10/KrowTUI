#include <K10-K10/core/drawObj.h>
#include <K10-K10/core/screen.h>

namespace __krow__ {
void DrawObj::put(int y, int x, const Cell& c) {
  __krow__::screen.put(x, y, c);
  return;
}

DrawObj drawObj;

}  // namespace __krow__
