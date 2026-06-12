#ifndef INCLUDE_APP_APP_H_
#define INCLUDE_APP_APP_H_

#include <K10-K10/core/render.h>
#include <K10-K10/core/screen.h>

#include <csignal>
#include <functional>

namespace __terminal__ {
class App {
 public:
  explicit App(Render& r);
  void init(int fps = 60);
  void loop(std::function<void()> frame);
  void stop();

 protected:
  bool runnning = false;
  bool pose_ = false;
  static std::sig_atomic_t sig_num;

 private:
  Render& render;
  int width = 0, height = 0;
  int fps = 60;
  static void signal_handler(int sig);
};
}  // namespace __terminal__
#endif
