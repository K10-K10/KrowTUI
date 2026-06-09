# List

`List` is an object that can render a list of items with various styles. It can be used to display a list of options, a menu, or any other type of list.

## API List

### 1. `position(rect)`

- __Arguments__: `rect: terminal::Rect` (a `Rect` object that defines the position and size of the list)
- __Return__: None

Sets the position and size of the list.

### 2. `items(items)`

- __Arguments__: `items: std::vector<std::string>` (a vector of strings containing the items to display in the list)
- __Return__: None

Sets the items to display in the list.

### 3. `add_item(item)`

- __Arguments__: `item: std::string` (a string containing the item to add to the list)
- __Return__: None

Adds an item to the list.

### 4. `move_up()`

- __Arguments__: None
- __Return__: None

Moves the selection up by one item.

### 5. `move_down()`

- __Arguments__: None
- __Return__: None

Moves the selection down by one item.

### 6. `items()`

- __Arguments__: None
- __Return__: `std::vector<std::string>` : A vector of strings containing the current items in the list.

Returns the current items in the list.

### 7. `selected_item()`

- __Arguments__: None
- __Return__: `std::string` : A string containing the currently selected item in the list.

Returns the currently selected item in the list.

### 8. `draw()`

- __Arguments__: None
- __Return__: None

Draws the list on the terminal at the specified position and with the specified styles.

---

version: *1.1.0*
author: *K10-K10*
update: 09/06/2026
