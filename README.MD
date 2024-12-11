# The Hour programming language

# Recognized keywords
 - `for`
 - `if`
 - `else`
 - `return`
 - `function`

# Builtin types/conversion functions
  - `int`: 4 Byte signed int
  - `float`: 4 Byte float
  - `bool`: Boolean value
  - `string`: String Object
  - `array`: Array Object

# Builtin Functions
 - I/O
   - `print(v...)`: Write to stdout without printing a newline. Returns null
   - `println(v...)`: Write to stdout with a newline. Returns null
   - `input()`: Reads a line of input from stdin. Returns `string`
 - Conversion
   - `string(v)`: Converts the variable to a `string` type
   - `int(v)`: Converts the variable to a `int` type
   - `bool(v)`: Converts the variable to a `bool` type
   - `float(v)`: Converts the variable to a `float` type
   - `array(v1, v2, ...)`: Initialize a array with multiple values
 - Math
   - `min(x, y)`: Returns the smaller value
   - `max(x, y)`: Returns the bigger value
   - `mod(x, y)`: Returns x MOD y 
   - `randomInt(min, max)`: Returns a random int (inclusive)
   - `random()`: Returns a random scalar `float`
 - Object Manipulation
   - `append(obj, itm)`: Appends `itm` onto `obj`. Returns modified `obj`
   - `get(obj, idx)`: Get position `idx` inside of `obj`. Returns item or null
   - `set(obj, idx, itm)`: Set position `idx` to `itm`. Returns updated object
   - `size(v)`: Returns the size of the presented object, only works on `string` and `array`
   - `type(v)`: Returns a `string` with the datatype of a value
   - `pop(obj)`: Pops a item off the `obj`. Returns the modified `obj`.
   - `erase(obj, start, n)`: Erase items from `obj`

# Examples are in `examples` folder