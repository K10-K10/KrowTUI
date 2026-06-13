#ifndef INCLUDE_CORE_RENDER_H_
#define INCLUDE_CORE_RENDER_H_

#include <K10-K10/core/screen.h>

#include <string>
namespace __terminal__ {
std::string makeline(const __terminal__::Cell& c);

class Render {
 public:
  explicit Render() = default;
  ~Render() = default;
  static void flush();
};

}  // namespace __terminal__
#endif
