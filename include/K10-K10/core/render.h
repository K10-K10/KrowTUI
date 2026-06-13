#ifndef INCLUDE_CORE_RENDER_H_
#define INCLUDE_CORE_RENDER_H_

#include <K10-K10/core/screen.h>

#include <string>
namespace __terminal__ {
class Render {
 public:
  explicit Render() = default;
  ~Render() = default;
  static void flush();

 private:
  std::string makeline(const __terminal__::Cell& c);
};

}  // namespace __terminal__
#endif
