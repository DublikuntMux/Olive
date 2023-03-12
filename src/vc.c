// C implementation of the Virtual Console (VC)
//
// # Usage
// ```c
// // demo.c
// // vc.c expectes render() to be defined and also supplies it's own entry
// point
// // if needed (some platforms like WASM_PLATFORM do not have the main()
// // entry point)
// #include "vc.c"
//
// #define WIDTH 800
// #define HEIGHT 600
// static uint32_t pixels[WIDTH*HEIGHT];
//
// static Olivec_Canvas vc_render(float dt)
// {
//     Olivec_Canvas oc = olivec_canvas(pixels, WIDTH, HEIGHT, WIDTH);
//     // ...
//     // ... render into oc ...
//     // ...
//     return oc;
// }
// ```
//
// # Build
// ```console
// $ clang -o demo.sdl -DVC_PLATFORM=VC_SDL_PLATFORM demo.c -lSDL2
// $ clang -o demo.term -DVC_PLATFORM=VC_TERM_PLATFORM demo.c
// $ emcc -fno-builtin --no-standard-libraries -Wl,--no-entry
// -sUSE_SDL=2 -sLEGACY_GL_EMULATION
// -Wl,--export=render -Wl,--allow-undefined -o demo.wasm
// -DVC_PLATFORM=VC_WASM_PLATFORM demo.c
// ```

#include "olive.c"

Olivec_Canvas vc_render(float dt);

#ifndef VC_PLATFORM
#error "Please define VC_PLATFORM macro"
#endif

// Possible values of VC_PLATFORM
#define VC_WASM_PLATFORM 0
#define VC_SDL_PLATFORM 1
#define VC_TERM_PLATFORM 2

#if VC_PLATFORM == VC_SDL_PLATFORM
#include "frontend/sdl.c"

#elif VC_PLATFORM == VC_TERM_PLATFORM
#include "frontend/term.c"

#elif VC_PLATFORM == VC_WASM_PLATFORM
#include "frontend/web.c"

#else
#error "Unknown VC platform"
#endif // VC_PLATFORM
