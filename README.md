# vector_c

`std::vector` in C++ implemented simply and minimally in C.  
The repository contains general purpose one `vector` which you need to cast to specific struct and supply creation function with size of struct.

It allocate more memory space to reduce calling to expensive call to `realloc()`. It uses 1.5 as factor of increasing elements the same as in `std::vector`.

# Build & Run

It's based on autotools. Execute the following

* `./configure`
* `make`
* (optional) `make check`
* `make install` - will install both static, shared library included header files to your system

# Note

Use `vector.h` and `vector.c` to integrate with your main source code.  
See example code at `vector_test.c`.

This one will do deep copy for input data, so it won't be mess or broken when you change input data from outside, it's separate.
It also accepts custom memory freeing function if your element needs a proper memory care. Just set its `free_element` function pointer to your function imeplementation via `free_element(void* element)` signature.

When using `vector_clear()` it will shrink down allocated memory to `estimatedLen` which is sent to `vector_new()` at first time, and will expand again if needed.

# License

[MIT](https://github.com/haxpor/vector_c/blob/master/LICENSE), Wasin Thonkaew
