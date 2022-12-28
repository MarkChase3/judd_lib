# JUDD_CORE

That module should be the core of everything, with interfaces to work with other modules and even other APIs. The idea is to make that with the least functions and types possible. It also should support windows, linux and emscripten (I don't have a Mac lol).


# Starting by the start

Let's include the files on each platform and as this will be a single header module, we should do a stb-like structure:

´´´
    #ifndef JUDD_CORE_H
    #ifdef __linux__
    #include <X11/Xlib.h>
    #endif
    #ifdef __WIN32__
    #include <windows.h>
    #endif
    #ifdef __EMSCRIPTEN__
    #include <emscripten.h>
    #endif
    #endif
    #ifdef JUDD_CORE_IMPL
    #undef JUDD_CORE_IMPL
    
    #endif
´´´

´´´
To compile:
* Linux: gcc -o judd_core judd_core.c
* Windows: gcc -o judd_core.exe judd_core.c
* Emscripten: emcc -o judd_core.html judd_core.c
´´´

Now let`s do some types:

´´´
typedef struct JUDD_DISPLAY_STRUCT judd_display_t;
typedef char judd_keyboard_state[256];
typedef struct JUDD_IMAGE_STRUCT judd_image_t;
´´´

´´´
Tip: Don't be scared with the judd_keyboard_state[256], that's how typedefs work in C. Give a look at *typedef array C* on google.
´´´
