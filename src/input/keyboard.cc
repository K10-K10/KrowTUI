#include <K10-K10/input/keyboard.h>
#include <K10-K10/utils/base.h>
#include <ncurses.h>

#include <iostream>
#include <string>

namespace __terminal__::__input__ {
Key::Key() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  is_visible = false;
};

KeyCode Key::getKeyCode() {
  KeyCode key_ = key_code;
  key_code = KeyCode::NONE;
  return key_;
}
char Key::getCurrentChar() {
  char char_ = current_char;
  current_char = '\0';
  return char_;
}

bool Key::read() {
  int ch = getch();
  if (ch == ERR) return false;

  key_code = KeyCode::UNKNOWN;
  current_char = 0;

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

  if (is_visible) terminal::utils::backSpace();
  return true;
}

Key::~Key() { endwin(); };
}  // namespace __terminal__::__input__

namespace terminal::input {
__terminal__::__input__::Key key;
}  // namespace terminal::input
