# Olive.c

<p align="center">
<img src="./assets/olivec-200.png">
</p>

**IMPORTANT! THIS LIBRARY IS A WORK IN PROGRESS! ANYTHING CAN CHANGE AT ANY
MOMENT WITHOUT ANY NOTICE! USE THIS LIBRARY AT YOUR OWN RISK!**

Simple graphics library that renders everything into the given memory pixel by
pixel.

The library is not concerned with displaying the image. It only fills up the
memory with pixels. It's up to you what to do with those pixels.

The name is pronounced as "olivets'" which is a Ukrainian word for "
pencil" (["олівець"](https://translate.google.com/?sl=uk&tl=en&text=%D0%BE%D0%BB%D1%96%D0%B2%D0%B5%D1%86%D1%8C&op=translate)).

## Quick Example (Flag of Japan)

_This example also
uses [stb_image_write.h](https://raw.githubusercontent.com/nothings/stb/master/stb_image_write.h)
to create the PNG image_

```c
// flag_jp.c
#include "olive.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define WIDTH 900
#define HEIGHT 600

uint32_t pixels[WIDTH*HEIGHT];

int main(void)
{
    Olive_Canvas oc = olive_canvas(pixels, WIDTH, HEIGHT, WIDTH);
    // Taken from https://upload.wikimedia.org/wikipedia/en/9/9e/Flag_of_Japan.svg
    olive_fill(oc, 0xFFFFFFFF);
    olive_circle(oc, WIDTH/2, HEIGHT/2, 180, 0xFF2D00BC);

    const char *file_path = "flag_jp.png";
    if (!stbi_write_png(file_path, WIDTH, HEIGHT, 4, pixels, sizeof(uint32_t)*WIDTH)) {
        fprintf(stderr, "ERROR: could not write %s\n", file_path);
        return 1;
    }
    return 0;
}
```

## Building the Tests and Demos

For build use SCons build system

```console
// before all build tools for copiling and run it
scons clang=True lto=True optimize=speed target=tools
scons target=prepare

// for sdl demos
scons clang=True lto=True optimize=speed target=native_sdl
// for terminal demos
scons clang=True lto=True optimize=speed target=native_term
// for web demos
scons clang=True lto=True optimize=speed target=web

// for building tests
scons lto=True target=tests
```

## Tests

Run the tests:

```console
./build/test run
```

If the expected behavior of the library has changed in the way that breaks
current test cases, you probably want to update them:

```console
./build/test update
```

For more info see the help:

```console
./build/test help
```

## Demos

The source code for demos is located at [demos](./demos/). Each demo is compiled
for 3 different "platforms" that is 3 different ways to display the generated
images:

1. [SDL](https://www.libsdl.org/) -- displays the images
   via [SDL_Texture](https://wiki.libsdl.org/SDL_Texture).
2. Terminal -- converts the images into ASCII art and prints them into the
   terminal.
3. WASM -- displays the images
   in [HTML5 canvas](https://developer.mozilla.org/en-US/docs/Web/API/Canvas_API)

To run the SDL version of a demo do

```console
./build/demos/<demo>.sdl
```

To run the Terminal version of a demo do

```console
./build/demos/<demo>.term
```

To run the WASM versions of the demos locally do

```console
python3 -m http.server 6969
iexplore.exe http://localhost:6969/
```

### Virtual Console

The support for several platforms is provided by Demo Virtual Console. It is
implemented in two files:

- [./demos/helpers/vc.c](./demos/helpers/vc.c) -- the C runtime required by all
  platforms.
- [./html/js/vc.js](./html/js/vc.js) -- the JavaScript runtime for running in a
  browser when compiled to WebAssembly.

The Demo Virtual Console is not part of the main library and is designed
specifically for demos. (I do consider including it into the main library, '
cause it looks pretty useful. The library is still in development).
