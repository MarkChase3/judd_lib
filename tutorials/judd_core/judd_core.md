# JUDD_CORE

That module should be the core of everything, with interfaces to work with other modules and even other APIs. The idea is to make that with the least functions and types possible. It also should support windows, linux and emscripten (I don't have a Mac lol).


## Starting by the start

Let's include the files on each platform and as this will be a single header module, we should do a stb-like structure:

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

      /**
      * To compile;
      * Linux: gcc -o judd_core judd_core.c
      * Windows: gcc -o judd_core.exe judd_core.c
      * Emscripten: emcc -o judd_core.html judd_core.c 
      */


Now let's do the main type:

    typedef struct JUDD_DISPLAY_STRUCT judd_display_t;

They will be better defined on the implementation part.

Let's start the functions declarations:

    void judd_start(); /* Init stuff */
    void judd_end(); /* End stuff */*

    judd_display_t *judd_create_window(int w, int h, char *name); /* create a window and put platform dependent stuff on that (with endifs of course) */
    void judd_change_display_property(judd_display_t *display, char *property, void *value); /* Set a display porperty  (like name, position on screen, width, or even events */
    void *judd_get_display_property(judd_display_t *display, char *name);
    void judd_update_display(judd_display_t *display); /* Update the display with platform dependent stuff */
    void judd_close_display(judd_display_t *display) /* Close the display and the platform dependent stuff */

That's it! We declared all the stuff.  I I've tried to be the simpler as possible and I think I got it.


Now let's implement somethings.

## Implementation

TODO