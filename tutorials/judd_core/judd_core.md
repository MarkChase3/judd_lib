# JUDD_CORE

That module should be the core of everything, with interfaces to work with other modules and even other APIs. The idea is to make that with the least functions and types possible. It also should support windows, linux and emscripten (I don't have a Mac lol). The main idea here is to do window management end opengl context creation easily and tiny.

## Starting by the start

    In all the code we will compile as the following:

      * Linux: gcc -o judd_core judd_core.c -lX11 -lGL -lGLX
      * Windows: gcc -o judd_core.exe judd_core.c -lgdi32
      * Emscripten: emcc -o judd_core.html judd_core.c 


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


Now let's do the main type:

    typedef struct JUDD_DISPLAY_STRUCT judd_display_t;


It will be better defined on the implementation part.

And a more specifc thing (made for doing a shortuct in the getters and setters):

    enum {  
        JUDD_DISPLAY_W,
        JUDD_DISPLAY_H,
        JUDD_DISPLAY_X,
        JUDD_DISPLAY_Y,
        JUDD_DISPLAY_RESIZED,
        JUDD_DISPLAY_CLOSED,
        JUDD_DISPLAY_MINIMIZED,
        JUDD_DISPLAY_MAXIMIZED,
        JUDD_DISPLAY_FULL,
        JUDD_DISPLAY_EVENT_RESIZE,
        JUDD_DISPLAY_EVENT_CLOSED,
        JUDD_DISPLAY_EVENT_MINIMIZED,
        JUDD_DISPLAY_EVENT_MAXIMIZED,
        JUDD_DISPLAY_EVENT_FULL
    }



And some keyboard enums:

    #ifdef __linux__
    enum {
    JUDD_KEY_A = XK_A, JUDD_KEY_B = XK_B, JUDD_KEY_C = XK_C, JUDD_KEY_D = XK_D,
    JUDD_KEY_E = XK_E, JUDD_KEY_F = XK_F, JUDD_KEY_G = XK_G, JUDD_KEY_H = XK_H,
     JUDD_KEY_I = XK_I, JUDD_KEY_J = XK_J, JUDD_KEY_K = XK_K, JUDD_KEY_L = XK_L,
     JUDD_KEY_M = XK_M, JUDD_KEY_N = XK_N, JUDD_KEY_O = XK_O, JUDD_KEY_P = XK_P,
     JUDD_KEY_Q = XK_Q, JUDD_KEY_R = XK_R, JUDD_KEY_S = XK_S, JUDD_KEY_T = XK_T,
    JUDD_KEY_U = XK_U, JUDD_KEY_V = XK_V, JUDD_KEY_W = XK_W, JUDD_KEY_X = XK_X,
    JUDD_KEY_Y = XK_Y, JUDD_KEY_Z = XK_Z,
    JUDD_KEY_0 = XK_0, JUDD_KEY_1 = XK_0, JUDD_KEY_2 = XK_0, JUDD_KEY_3 = XK_0,
    JUDD_KEY_4 = XK_0, JUDD_KEY_5 = XK_0, JUDD_KEY_6 = XK_0, JUDD_KEY_7 = XK_0,
    JUDD_KEY_8 = XK_0, JUDD_KEY_9 = XK_9,
    JUDD_KEY_SPACE = XK_space, JUDD_KEY_ENTER = XK_Return, JUDD_KEY_SHIFT = XK_Shift_L, 
    JUDD_KEY_CNTRL = XK_Control_L, JUDD_KEY_BAKCSPACE =    XK_BackSpace,
    };
    #endif
    #ifdef _WIN32
    enum {
    JUDD_KEY_A = 'a', JUDD_KEY_B = 'b', JUDD_KEY_C = 'c', JUDD_KEY_D = 'd',
     JUDD_KEY_E = 'e', JUDD_KEY_F = 'f', JUDD_KEY_G = 'g', JUDD_KEY_H = 'h',
     JUDD_KEY_I = 'i', JUDD_KEY_J = 'j', JUDD_KEY_K = 'k', JUDD_KEY_L = 'l',
     JUDD_KEY_M = 'm', JUDD_KEY_N = 'n', JUDD_KEY_O = 'o', JUDD_KEY_P = 'p',
    JUDD_KEY_Q = 'q', JUDD_KEY_R = 'r', JUDD_KEY_S = 's', JUDD_KEY_T = 't',
    JUDD_KEY_U = 'u', JUDD_KEY_V = 'v', JUDD_KEY_W = 'w', JUDD_KEY_X = 'x',
    JUDD_KEY_Y = 'y', JUDD_KEY_Z = 'z',
    JUDD_KEY_0 = VK_0, JUDD_KEY_1 = VK_1, JUDD_KEY_2 = VK_2, JUDD_KEY_3 = VK_3,
    JUDD_KEY_4 = VK_4, JUDD_KEY_5 = VK_5, JUDD_KEY_6 = VK_6, JUDD_KEY_7 = XK_7,
    JUDD_KEY_8 = VK_8, JUDD_KEY_9 = VK_9,
    };
    #endif
    enum {JUDD_KEY_UP, JUDD_KEY_RELEASED, JUDD_KEY_PRESSED, JUDD_KEY_DOWN}; 
Let's also implement an event type, for window events:

    typedef void(*judd_event_t)(judd_display_t *display);

Let's start the functions declarations:

    judd_display_t *judd_create_window(int w, int h, char *name); /* create a window and put platform dependent stuff on that (with endifs of course) */
    void judd_change_display_property(judd_display_t *display, int property, void *value); /* Set a display property  (like name, position on screen, width, or even events */
    void *judd_get_display_property(judd_display_t *display, char *name);
    judd_event_t judd_get_display_event(judd_display_t *display, int property);
    void judd_set_display_event(judd_display_t *display, int property, judd_event_t event);
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

Now let's do the setters:

     void judd_set_display_property(judd_display_t *display, int property, long long int value){
        if(property == JUDD_DISPLAY_W) display->w = value;
        if(property == JUDD_DISPLAY_H) display->h = value;
        if(property == JUDD_DISPLAY_X) display->x = value;
        if(property == JUDD_DISPLAY_Y) display->y = value;
        if(property == JUDD_DISPLAY_RESIZED) display->resized = value;
        if(property == JUDD_DISPLAY_CLOSED) display->closed = value;
        if(property == JUDD_DISPLAY_MINIMIZED) display->minimized = value;
        if(property == JUDD_DISPLAY_FULL) display->full = value;
    }
    void judd_set_display_event(judd_display_t *display, int property, judd_event_t event){
        if(property == JUDD_DISPLAY_EVENT_RESIZE) display->event_resize = event;
        if(property == JUDD_DISPLAY_EVENT_CLOSE) display->event_close = event;
        if(property == JUDD_DISPLAY_EVENT_MINIMIZE) display->event_minimize = event;
        if(property == JUDD_DISPLAY_EVENT_MAXIMIZE) display->event_maxmize = event;
    }
    

I will let the getters implementation for the reader as an exercise (And because I don't want to fill this tutorial with the same lines of code). If you have any doubt, look at the finished code, it probably is on the same folder as this file.

Now let's implement the `judd_update_display`

    void judd_update_display(judd_display_t *display){
        #ifdef __linux__
        
        #endif
        #ifdef _WIN32
        
        #endif
        #ifdef __EMSCRIPTEN__
        
        #endif
    }

Let's do the linux part:
        
    while (XPending(display->display)) { // Keep the display openned and say if there's some event
        XEvent event;
        char k;
        XNextEvent(display->display, &event); // Get next event
        switch (event.type) {
            case KeyPress:
                k = XLookupKeysym(&event.xkey, 0); // Get XK_{key_pressed}
                if(k - XK_a < 26) k = XK_A + (k - XK_a); // Translate it to the uppercase if is lower (We don't d>                display->keys[k] = JUDD_KEY_PRESSED;
            break;
            case KeyRelease:
                k = XLookupKeysym(&event.xkey, 0); // Get XK_{key_pressed}
                if(k - XK_a < 26) k = XK_A + (k - XK_a); // Translate it to the uppercase if is lower (We don't d>
                display->keys[k] = JUDD_KEY_RELEASED;
           break;
       }
    }


