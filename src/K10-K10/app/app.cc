#include <K10-K10/app/app.h>
#include <K10-K10/core/render.h>
#include <K10-K10/core/screen.h>
#include <K10-K10/utils/base.h>
#include <termios.h>
#include <unistd.h>

#include <chrono>
#include <csignal>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <thread>
#include <tuple>

namespace __krow__ {
termios orig;

void enable_raw_mode() {
  tcgetattr(STDIN_FILENO, &orig);

  termios raw = orig;
  raw.c_lflag &= ~(ECHO | ICANON);

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disable_raw_mode() { tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig); }
int __krow__::App::sig_num = 0;

App::App(Render& r) noexcept : render(r){};

void App::signal_handler(int sig) { sig_num = sig; }

void App::init(int fps) {
  std::signal(SIGINT, App::signal_handler);
  std::signal(SIGWINCH, App::signal_handler);

  std::cout << "\x1b[?1049h" << std::flush;
  std::cout << "\x1b[?25l" << std::flush;
  enable_raw_mode();
  std::tie(width, height) = krow::utils::getkrowSize();
  __krow__::screen.resize(width, height);
  this->fps = fps;
}

void App::loop(const std::function<void()>& frame) {
  runnning = true;
  while (runnning) {
    if (sig_num == SIGWINCH) {
      std::tie(width, height) = krow::utils::getkrowSize();
      krow::utils::clear();
      __krow__::screen.resize(width, height);
      sig_num = 0;
    }
    if (sig_num == SIGINT) {
      stop();
      std::exit(0);
    }
    frame();
    __krow__::Render::flush();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
}

void App::stop() {
  runnning = false;
  std::cout << "\x1b[?1049l" << std::flush;
  std::cout << "\x1b[?25h" << std::flush;
  disable_raw_mode();
}

}  // namespace __krow__
