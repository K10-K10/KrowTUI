#ifndef INCLUDE_APP_APP_H_
#define INCLUDE_APP_APP_H_

#include <K10-K10/core/render.h>
#include <K10-K10/core/screen.h>

#include <csignal>
#include <functional>

namespace __krow__ {
class App {
 public:
  explicit App(Render& r) noexcept;
  void init(int fps = 60);
  void loop(const std::function<void()>& frame);
  void stop();

 protected:
  void set_running(bool flag);
  bool get_running();
  void set_pose(bool flag);
  bool get_pose();

  static std::sig_atomic_t sig_num;

 private:
  Render& render;
  bool runnning = false;
  bool pose_ = false;
  int width = 0, height = 0;
  int fps = 60;
  static void signal_handler(int sig);
};
}  // namespace __krow__
#endif
