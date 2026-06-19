# Block

`Block` is an object that can render a rectangular frame with a border. It can be used to create sections or containers in your app's interface.

## Methods

- [`position(rect)`](#1-positionrect): Sets the position and size of the block.
- [`draw()`](#2-draw): Draws the block on the terminal at the specified position and with the specified border style.

### Style Methods

- [`border_type(border)`](#3-borderborder): Sets the border style of the block.
- [`borders(type)`](#4-bordersborder): Specifies the drawing direction of the block's border.
- [`border_color(color)`](#5-bordercolorcolor): Sets the color of the block's border.
- [`field_color(color)`](#6-fieldcol  orcolor): Sets the background color of the block.

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

- __Arguments__: `rect: krow::Rect` (a `Rect` object that defines the position and size of the block)
- __Return__: None

Sets the position and size of the block.

### 2. `draw()`

```cpp
void draw();
```

- __Arguments__: None
- __Return__: None

Draws the block on the terminal at the specified position and with the specified border style.

### 3. `border_type(border)`

```cpp
Block& border_type(krow::BorderType border);
```

- __Arguments__: `border: krow::BorderType` (Specifies the border style)
- __Return__: None

Sets the border style of the block. The [`BorderType`](#bordertype) can be one of the following:

### 4. `borders(type)`

```cpp
Block& borders(krow::EdgeType type);
```

- __Arguments__: `type: krow::EdgeType` (Specifies the drawing direction)
- __Return__: None

Specifies the drawing direction of the block's border. The [`EdgeType`](#edgetype) can be one of the following:

### 5. `border_color(color)`

```cpp
Block& border_color(krow::Color color);
Block& border_color(int color);
```

- __Arguments__: `color: krow::Color` / `int` (Specifies the color of the border)
- __Return__: None

Sets the color of the block's border.

### 6. `field_color(color)`

```cpp
Block& field_color(krow::Color color);
Block& field_color(int color);
```

- __Arguments__: `color: krow::Color` / `int` (Specifies the color of the background)
- __Return__: None

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

---

__version__: *0.2.0* | __author__: *K10-K10* | __update__: 11/06/2026
