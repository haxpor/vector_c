# vector_c

`std::vector` in C++ implemented simply and minimally in C.  
The repository contains specific type `vectorDot` using with `struct Dot`, and general purpose one `vector` which you need to cast to specific struct and supply creation function with size of struct.

# Build & Run

Build the project with `make`.  
You will see two executable files `vector`, and `vectorDot`.

Clean with `make clean`.

# Note

## Specific struct

Use `vectorDot.h` and `vectorDot.c` to integrate with your main source code.  
See example code at `vectorDot_test.c`.

This type passes by value.

## General purpose

Use `vector.h` and `vector.c` to integrate with your main source code.  
See example code at `vector_test.c`.

General purpose always passes by reference.

# License

[MIT](https://github.com/haxpor/vector_c/blob/master/LICENSE), Wasin Thonkaew
