# JUDD_CORE

That module should be the core of everything, with interfaces to work with other modules and even other APIs. The idea is to make that with the least functions and types possible. It also should support windows, linux and emscripten (I don't have a Mac lol). The main idea here is to do window management end opengl context creation easily and tiny.


## Starting by the start

Let's include the files on each platform and as this will be a single header module, we should do a stb-like structure:

    #ifndef JUDD_CORE_H
    #ifdef __linux__
    #include <X11/Xlib.h>
    #include <Gl/glx.h>
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

    judd_display_t *judd_create_window(int w, int h, char *name); /* create a window and put platform dependent stuff on that (with endifs of course) */
    void judd_change_display_property(judd_display_t *display, char *property, void *value); /* Set a display porperty  (like name, position on screen, width, or even events */
    void *judd_get_display_property(judd_display_t *display, char *name);
    void judd_update_display(judd_display_t *display); /* Update the display with platform dependent stuff */
    void judd_close_display(judd_display_t *display) /* Close the display and the platform dependent stuff */

That's it! We declared all the stuff.  I I've tried to be the simpler as possible and I think I got it.


Now let's implement somethings.

## Implementation

Let's start implementing the first and only type: `judd_display_t`:

    typedef struct JUDD_DISPLAY_STRUCT {
        int w;
        int h;
        char *name;
        #ifdef __linux__
        Window window;
        Display display;
        Screen screen;
        GC graphics_context;
        GLXContext glx_context;
        #endif
        #ifdef _WIN32
        HWND window;
        #endif
        #ifdef __EMSCRIPTEN__
        WebGlContext ctx;
        #endif
    }

Let's do an `judd_create_display` function:

    judd_display_t *judd_create_display(){
        #ifdef __linux__
        
        #endif
        #ifdef _WIN32
        
        #endif
        #ifdef __EMSCRIPTEN__
        
        #endif
    }

For the sake of reading, we will implement every platform dependent code separated.

But first, let's do a multi-platform work:

    judd_display_t *judd_create_display(int x, int y, int w, int h, char *name){
    judd_display_t *display = malloc(sizeof(judd_display_t));
    display->w = display->w;
    display->h = display->h;
    display->x = display->x;
    display->y = display->y;
    strcpy(display->name, name);
    // The ifdefs come here
    }

Now, let's implement the linux part:

    display->display = XOpenDisplay(NULL); // Opens a display
    display->screen = XDefaultScreen(display->display); // Get's the default screen
    display->window = XCreateSimpleWindow(display->display, RootWindow(display->display, display->screen), 10, 10>    XSelectInput(display->display, display->window, ExposureMask | KeyPressMask); // Select the window types
    XMapWindow(display->display, display->window); // Join the display and the window

Now, the windows code:

    WNDCLASS wc = {
        .style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW,
        .lpfnWndProc = DefWindowProcA,
        .cbClsExtra = 0,
        .cbWndExtra = 0,
        .hInstance = GetModuleHandleA(NULL),
        .hIcon = LoadIconA(NULL, IDI_APPLICATION),
        .hCursor = LoadCursorA(NULL, IDC_ARROW),
        .hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1),
        .lpszMenuName = NULL,
        .lpszClassName = name,
    }; // Creates a proper win32 window class
    RegisterClassA(&wc); // register the window class
    display->window = CreateWindowExA(0, name, name, WS_OVERLAPPEDWINDOW|WS_VISIBLE, CW_USEDEFAULT, w, h, NULL, NULL, GetModuleHandle(NULL), NULL); // create the real window

And the emscripten:

    display->context = emscripten_webgl_create_context("canvas", 0); // creates the context
    emscripten_webgl_make_context_current(display->context); // makes the context current;
    

Now the `judd_set_property` and `judd_get_property`.

    /* TODO */
