#ifndef INCLUDE_INPUT_KEYBOARD_H_
#define INCLUDE_INPUT_KEYBOARD_H_

#include <chrono>
#include <cstdint>

namespace __krow__::__input__ {
enum class KeyCode : std::uint8_t {
  NONE,
  UNKNOWN,
  ESC,
  ENTER,
  BACKSPACE,
  TAB,
  UP,
  DOWN,
  LEFT,
  RIGHT,
  SPACE,
  CHAR,
  // Add other key codes as needed
};

class Key {
 public:
  explicit Key();
  ~Key();

  KeyCode getKeyCode();
  char getCurrentChar();
  bool read();

 private:
  std::chrono::steady_clock::time_point last_input_time;
  KeyCode key_code = KeyCode::NONE;
  char current_char = 0;
  bool is_visible = false;

  enum class KeyState : std::uint8_t {
    PRESSED,
    RELEASED
  } key_state = KeyState::RELEASED;
  enum class Modifier : std::uint8_t {
    NONE = 0,
    SHIFT = 1,
    CTRL = 2,
    ALT = 4
  } modifier = Modifier::NONE;
};

}  // namespace __krow__::__input__

namespace krow::input {
extern __krow__::__input__::Key key;
using KeyCode = __krow__::__input__::KeyCode;
}  // namespace krow::input

#endif
