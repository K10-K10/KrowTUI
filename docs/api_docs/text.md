# Text

`Text` is an object that can render a string label. It can be used to display static text.

## API List


### 1. `Text` constructor

- __Arguments__: None
- __Return__: N/A

Creates a new `Text` object.

### 2. `position(rect)`

- __Arguments__: `rect: terminal::Rect` (a `Rect` object that defines the position and size of the text)
- __Return__: None

Sets the position and size of the text.

### 3. `content(content)`

- __Arguments__: `content: std::string` (a string containing the text to display)
- __Return__: None

Sets the text content of the `Text` object.

### 4. `get_text()`

- __Arguments__: None
- __Return__: `std::string` : A string containing the current text content of the `Text` object.

Returns the current text content of the `Text` object.

### 5. `draw()`

- __Arguments__: None
- __Return__: None

Draws the text on the terminal at the specified position and with the specified styles.

---

version: *1.1.0*
author: *K10-K10*
update: 09/06/2026
