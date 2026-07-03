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
#include <string>
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
  std::tie(width, height) = krow::utils::getTerminalSize();
  __krow__::screen.resize(width, height);
  this->fps = fps;
  runnning = true;
}

void App::loop(const std::function<void()>& frame) {
  while (runnning) {
    if (sig_num == SIGWINCH) {
      std::tie(width, height) = krow::utils::getTerminalSize();
      krow::utils::clear();
      __krow__::screen.resize(width, height);
      sig_num = 0;
    }
    if (sig_num == SIGINT) {
      leave();
      std::exit(0);
    }
    frame();
    if (!pose_) {
      __krow__::Render::flush();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000 / fps));
  }
}

void App::leave() {
  runnning = false;
  std::cout << "\x1b[?1049l" << std::flush;
  std::cout << "\x1b[?25h" << std::flush;
  disable_raw_mode();
  std::cout << std::flush;
  if (!logs_.empty()) {
    for (const std::string& s : logs_) {
      // FIXME: Why is it necessary to output carrige return explicitly?
      std::cout << s << "\r\n" << std::flush;
    }
  }
}

void App::attach() {
  pose_ = false;
  std::cout << "\x1b[?1049h" << std::flush;
  std::cout << "\x1b[?25l" << std::flush;
  enable_raw_mode();
  std::tie(width, height) = krow::utils::getTerminalSize();
  __krow__::screen.resize(width, height);
}

void App::detach() {
  pose_ = true;
  __krow__::screen.resize(0, 0);
  std::cout << "\x1b[?1049l" << std::flush;
  std::cout << "\x1b[?25h" << std::flush;
  disable_raw_mode();
}

}  // namespace __krow__
