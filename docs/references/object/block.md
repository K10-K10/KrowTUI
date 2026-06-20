---
version: 0.2.0
date: 19/06/2026
---

# Block

`Block` is an object that can render a rectangular frame with a border. It can be used to create sections or containers in your app's interface.

## Methods

- [`position(rect)`](#1-positionrect): Sets the position and size of the block.
- [`draw()`](#2-draw): Draws the block on the terminal at the specified position and with the specified border style.
- [`title(text)`](#3-titletext): Sets the title of the block, which will be displayed at the top center of the block.
- [`bottom_title(text)`](#4-bottom_titletext): Sets the bottom title of the block, which will be displayed at the bottom center of the block.

### Style Methods

- [`border_type(border)`](#1-border_typeborder): Sets the border style of the block.
- [`borders(type)`](#2-borderstype): Specifies the drawing direction of the block's border.
- [`border_color(color)`](#3-border_colorcolor): Sets the color of the block's border.
- [`field_color(color)`](#4-field_colorcolor): Sets the background color of the block.

## Example

```cpp
#include <K10-K10/krow.h>

int main() {
    krow::app.init();
    krow::Block block;
    block.position({1, 1, 20, 10})
         .border_type(BorderType::SINGLE)
         .borders(Borders::ALL)
         .border_color(krow::utils::TextColor::Red)
         .field_color(krow::utils::FillColor::Blue);

    krow::app.loop([&]() {
        block.draw();
    });

    krow::app.stop();
    return 0;
}

```

## Method Details

### 1. `position(rect)`

```cpp
Block& position(const Rect& r);

```

- **Arguments**: `rect: krow::Rect` (a `Rect` object that defines the position and size of the block)
- **Return**: `Block&` (Reference to the block for method chaining)

Sets the position and size of the block.

### 2. `draw()`

```cpp
void draw();

```

- **Arguments**: None
- **Return**: None

Draws the block on the terminal at the specified position and with the specified border style.

### 3. `title(text)`

```cpp
Block& title(const Text& text);

```

- **Arguments**: `text: krow::Text` (a `Text` structure that defines the content and style of the title)
- **Return**: `Block&` (Reference to the block for method chaining)

Sets the title of the block, which will be displayed at the top center of the block.

### 4. `bottom_title(text)`

```cpp
Block& bottom_title(const Text& text);

```

- **Arguments**: `text: krow::Text` (a `Text` structure that defines the content and style of the bottom title)
- **Return**: `Block&` (Reference to the block for method chaining)

Sets the bottom title of the block, which will be displayed at the bottom center of the block.

> [!WARNING]
> The `bottom_title` method is currently not working.
---

### 1. `border_type(border)`

```cpp
Block& border_type(krow::BorderType border);

```

- **Arguments**: `border: krow::BorderType` (Specifies the border style)
- **Return**: `Block&` (Reference to the block for method chaining)

Sets the border style of the block. The [`BorderType`](https://www.google.com/search?q=%23bordertype) can be one of the following:

### 2. `borders(type)`

```cpp
Block& borders(krow::EdgeType type);

```

- **Arguments**: `type: krow::EdgeType` (Specifies the drawing direction)
- **Return**: `Block&` (Reference to the block for method chaining)

Specifies the drawing direction of the block's border. The [`EdgeType`](https://www.google.com/search?q=%23edgetype) can be one of the following:

### 3. `border_color(color)`

```cpp
Block& border_color(krow::Color color);
Block& border_color(int color);

```

- **Arguments**: `color: krow::Color` / `int` (Specifies the color of the border)
- **Return**: `Block&` (Reference to the block for method chaining)

Sets the color of the block's border.

### 4. `field_color(color)`

```cpp
Block& field_color(krow::Color color);
Block& field_color(int color);

```

- **Arguments**: `color: krow::Color` / `int` (Specifies the color of the background)
- **Return**: `Block&` (Reference to the block for method chaining)

Sets the background color of the block.

---

## BorderType

The `BorderType` enum defines the styles of borders that can be applied to a `Block` object. The available border types are:

### element

- `Single`: A single line border.
- `Double`: A double line border.
- `Rounded`: A rounded corner border.
- `Thick`: A thick line border.

## EdgeType

The `EdgeType` enum defines the edges of the block where the border should be drawn. The available edge types are:

### element

- `All`: Draws the border on all edges of the block.
- `Top`: Draws the border only on the top edge of the block.
- `Bottom`: Draws the border only on the bottom edge of the block.
- `Left`: Draws the border only on the left edge of the block.
- `Right`: Draws the border only on the right edge of the block.
- `None`: No border is drawn.
