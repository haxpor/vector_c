# vector_c

`std::vector` in C++ implemented simply and minimally in C.  
The repository contains general purpose one `vector` which you need to cast to specific struct and supply creation function with size of struct.

It allocate more memory space to reduce calling to expensive call to `realloc()`. It uses 1.5 as factor of increasing elements the same as in `std::vector`.

# Build & Run

It's based on autotools. Execute the following

* `./autogen.sh`
* `./configure`
* `make`
* (optional) `make check`
* `make install` - will install both static, shared library included header files to your system

# Installation

## Debian/Ubuntu

* `sudo add-apt-repository ppa:haxpor/combined`
* `sudo apt install vector_c`

## NDK-BUILD support for Android

This project has support for building this library for Android.

It has `Android.mk` file at the root directory of this project.
You can use the following commands

```
ndk-build NDK_PROJECT_PATH=null NDK_OUT=build/objs NDK_LIBS_OUT=build/libs APP_BUILD_SCRIPT=Android.mk APP_PLATFORM=android-18 APP_MODULES="vector vector_static" NDK_DEBUG=1
```

That will generate obj and library (shared and static one) files at `build/objs` and `build/libs` (static library is at `build/objs/local` for minimum sdk support of api level 18 with debugging symbols also generated. `APP_MODULES` tells to build for both shared and static library.

# Note

Use `vector.h` and `vector.c` to integrate with your main source code.  
See example code at `vector_test.c`.

This one will do deep copy for input data, so it won't be mess or broken when you change input data from outside, it's separate.
It also accepts custom memory freeing function if your element needs a proper memory care. Just set its `free_element` function pointer to your function imeplementation via `free_element(void* element)` signature.

When using `vector_clear()` it will shrink down allocated memory to `estimatedLen` which is sent to `vector_new()` at first time, and will expand again if needed.

# License

[MIT](https://github.com/haxpor/vector_c/blob/master/LICENSE), Wasin Thonkaew
