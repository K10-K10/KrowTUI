#include <K10-K10/input/keyboard.h>
#include <K10-K10/utils/base.h>
#include <ncurses.h>

#include <chrono>

namespace __krow__::__input__ {
Key::Key() noexcept {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  is_visible = false;
};

KeyCode Key::getKeyCode() {
  const KeyCode key_ = key_code;
  key_code = KeyCode::NONE;
  return key_;
}
char Key::getCurrentChar() {
  const char char_ = current_char;
  current_char = '\0';
  return char_;
}

bool Key::read() {
  const int ch = getch();

  auto now = std::chrono::steady_clock::now();
  if (ch == ERR) {
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                       now - last_input_time)
                       .count();

    if (elapsed > 120) {
      key_code = KeyCode::NONE;
      current_char = '\0';
    }
    return false;
  }
  last_input_time = std::chrono::steady_clock::now();
  flushinp();

  switch (ch) {
    case KEY_UP:
      key_code = KeyCode::UP;
      break;
    case KEY_DOWN:
      key_code = KeyCode::DOWN;
      break;
    case KEY_LEFT:
      key_code = KeyCode::LEFT;
      break;
    case KEY_RIGHT:
      key_code = KeyCode::RIGHT;
      break;

    case 27:
      key_code = KeyCode::ESC;
      break;
    case '\n':
      key_code = KeyCode::ENTER;
      break;
    case '\t':
      key_code = KeyCode::TAB;
      break;
    case KEY_BACKSPACE:
    case 127:
      key_code = KeyCode::BACKSPACE;
      break;

    case ' ':
      key_code = KeyCode::SPACE;
      current_char = ' ';
      break;

    default:
      if (ch >= 0 && ch <= 255) {
        key_code = KeyCode::CHAR;
        current_char = static_cast<char>(ch);
      }
      break;
  }

  if (is_visible) {
    krow::utils::backSpace();
  }
  return true;
}

Key::~Key() { endwin(); };
}  // namespace __krow__::__input__

namespace krow::input {
__krow__::__input__::Key key;
}  // namespace krow::input
