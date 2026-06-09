# Block

`Block` is an object that can render a rectangular frame with a border. It can be used to create sections or containers in your app's interface.

## API List

### 1. `position(rect)`

- __Arguments__: `rect: terminal::Rect` (a `Rect` object that defines the position and size of the block)
- __Return__: None

Sets the position and size of the block.

### 2. `border(border)`

- __Arguments__: `border: terminal::BorderType` (Specifies the border style)
- __Return__: None

Sets the border style of the block. The [`BorderType`](#bordertype) can be one of the following:

### 3. `borders(type)`

- __Arguments__: `type: terminal::EdgeType` (Specifies the drawing direction)
- __Return__: None

Specifies the drawing direction of the block's border. The [`EdgeType`](#edgetype) can be one of the following:

### 4. `draw()`

- __Arguments__: None
- __Return__: None

Draws the block on the terminal at the specified position and with the specified border style.

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

__version__: *1.1.0*  
__author__: *K10-K10*  
__update__: 09/06/2026
