# bitr
A C and Lua **5.3** bit array implementation

## Purpose

A bit array can serve as a space-saving substitute for a boolean array.
A boolean is typically 1 byte. 8 times less space occupied begins to
become more significant the larger the array is.

The real advantage of using a bit array, however, is a consistent API:
attempts to index out of bounds will returns an error rather than
crash the program, intent is more clearly communicated, and it
reduces the chance of making mistakes when performing bitwise
operations to set, clear, and toggle bits.

## Usage overview

### C library: `bitr`

See also `src/bitr.h` for a good overview.

```C

/* initialize bit array big enough to hold n bits with all bits turned on */
struct bitr *b = Bitr_new(170, true);

/* initialize bit array big enough to hold n bits with all bits turned off */
struct bitr *b = Bitr_new(170, false);

/* set bit 17 */
Bitr_set(b, 17);

/* clear bit 17 */
Bitr_clear(b, 17);

/* toggle bit 7141 */
Bitr_toggle(b, 7141);

/* test bit 1 */
Bitr_test(b, 1);     // should return 1 if the bit is set, else 0 if unset

/* deallocate bit array */
Bitr_destroy(&b);

```
**NOTE**
In all cases, `-1` will be returned if the `n` is out of bounds.
For example, attempting to set bit 17 in a 10-bit array will return
`-1`.


### Lua library: `luabitr`

The lua library usage is almost a 1-to-1 of the C library.

```lua

-- require luabitr
local bitr = require("luabitr")

-- initialize bit array big enough to hold n bits with all bits turned on
local b = bitr.new(170, true)

-- initialize bit array big enough to hold n bits with all bits turned off
local b = bitr.new(170, false);  -- 2nd param can be ommitted if false

-- set bit 17
b:set(17)

-- clear bit 17
b:clear(17)

-- toggle bit 7141
b:toggle(7141)

-- test bit 1
b:test(1)     -- should return true if the bit is set, else false if unset

```
**NOTE**
that no destroy metamethod is provided -- or necessary -- in
Lua. The resources associated with the bit array will be automatically
freed by the Lua garbage collector once the object is no longer
anchored by any references.

**NOTE**
that attempting to index out of bounds _will_ throw an error in Lua -
unlike in C where an error code is returned. This is so because errors
can be _caught_ in Lua (i.e. protected calls can be made) which is
arguably clearer and more convenient then the return of an error code
which is likely to be missed.
More than the program crashing, C's problem is the likelihood of
a crash not occuring but the memory being corrupted by out-of-bounds
writes.

