#ifndef INCLUDE_CORE_RENDER_H_
#define INCLUDE_CORE_RENDER_H_

#include <K10-K10/core/screen.h>

#include <string>
namespace __krow__ {
std::string makeline(const __krow__::Cell& c);

class Render {
 public:
  explicit Render() = default;
  ~Render() = default;
  static void flush();
};

}  // namespace __krow__
#endif
