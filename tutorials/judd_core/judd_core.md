# JUDD_CORE

That module should be the core of everything, with interfaces to work with other modules and even other APIs. The idea is to make that with the least functions and types possible. It also should support windows, linux and emscripten (I don't have a Mac lol). The main idea here is to do window management end opengl context creation easily and tiny.

## Starting by the start

    In all the code we will compile as the following:

      * Linux: gcc -o judd_core judd_core.c -lX11 -lGL -lGLX
      * Windows: gcc -o judd_core.exe judd_core.c -lgdi32
      * Emscripten: emcc -o judd_core.html judd_core.c -sASYNCIFY


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

Let's start implementing the first and only structure: `judd_display_t`:

    typedef struct JUDD_DISPLAY_STRUCT {
        char keys[256];
        char *name;
        char closed;
        char full;
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
        int w;
        int h;
        #endif
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
    #ifdef __EMSCRIPTEN__
    enum {
        JUDD_KEY_A = 'A', JUDD_KEY_B = 'B', JUDD_KEY_C = 'C', JUDD_KEY_D = 'D',
        JUDD_KEY_E = 'E', JUDD_KEY_F = 'F', JUDD_KEY_G = 'G', JUDD_KEY_H = 'H',
        JUDD_KEY_I = 'I', JUDD_KEY_J = 'J', JUDD_KEY_K = 'K', JUDD_KEY_L = 'L',
        JUDD_KEY_M = 'M', JUDD_KEY_N = 'N', JUDD_KEY_O = 'O', JUDD_KEY_P = 'P',
        JUDD_KEY_Q = 'Q', JUDD_KEY_R = 'R', JUDD_KEY_S = 'S', JUDD_KEY_T = 'T',
        JUDD_KEY_U = 'U', JUDD_KEY_V = 'V', JUDD_KEY_W = 'W', JUDD_KEY_X = 'X',
        JUDD_KEY_Y = 'Y', JUDD_KEY_Z = 'Z',
        JUDD_KEY_0 = '0', JUDD_KEY_1 = '1', JUDD_KEY_2 = '2', JUDD_KEY_3 = '3',
        JUDD_KEY_4 = '4', JUDD_KEY_5 = '5', JUDD_KEY_6 = '6', JUDD_KEY_7 = '7',
        JUDD_KEY_8 = '8', JUDD_KEY_9 = '9',
        JUDD_KEY_SPACE = ' ', JUDD_KEY_ENTER = 13, JUDD_KEY_SHIFT = 16,
        JUDD_KEY_CNTRL = 17, JUDD_KEY_BAKCSPACE = 8,
    };
    #endif
    enum {JUDD_KEY_UP, JUDD_KEY_RELEASED, JUDD_KEY_PRESSED, JUDD_KEY_DOWN}; 


Let's start the functions declarations:

    judd_display_t *judd_create_window(int w, int h, char *name); /* create a window and put platform dependent stuff on that (with endifs of course) */
    void judd_set_display_name(judd_display_t *display, char *value);
    void judd_set_display_fullscreen(judd_display_t *display, char value);
    void judd_update_display(judd_display_t *display); /* Update the display with platform dependent stuff */
    void judd_close_display(judd_display_t *display) /* Close the display and the platform dependent stuff */

That's it! We declared all the stuff.  I I've tried to be the simpler as possible and I think I got it.

Now let's implement somethings.

## Implementation

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
    display->full = 0;
    display->closed = 0;
    strcpy(display->name, name);
    /* The ifdefs come here */
    }

Now, let's implement the linux part:

    display->display = XOpenDisplay(NULL); /* Opens a display */
    display->screen = XDefaultScreen(display->display); /* Get's the default screen */
    display->window = XCreateSimpleWindow(display->display, RootWindow(display->display, display->screen), 10, 10> XSelectInput(display->display, display->window, ExposureMask | KeyPressMask | KeyRelease); /* Select the window types*/
    XMapWindow(display->display, display->window); /* Join the display and the window */

Now, the windows code:

    /* The windows code is very extensive (100 lines). If you have a smaller version or can refactorize this to be smaller, please open a pull request */
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
    }; /* Creates a proper win32 window class */
    RegisterClassA(&wc); /* register the window class */
    display->window = CreateWindowExA(0, name, name, WS_OVERLAPPEDWINDOW|WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, w, h, NULL, NULL, GetModuleHandle(NULL), &display->window); // create the real window
    HDC real_dc = GetDC(display->window);
    HGLRC WINAPI(*wglCreateContextAttribsARB)(HDC, HGLRC, const int*);
    BOOL WINAPI(*wglChoosePixelFormatARB)(HDC, const int*,
    const FLOAT*, UINT, int*, UINT*);
    WNDCLASSA window_class = {
        .style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
        .lpfnWndProc = DefWindowProcA,
        .hInstance = GetModuleHandle(0),
        .lpszClassName = "Dummy WGL Window Class",
    };

    RegisterClassA(&window_class);
    HWND dummy_window = CreateWindowExA(
        0,
        window_class.lpszClassName,
        "Dummy OpenGL Window",
        0,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        0,
        0,
        window_class.hInstance,
        0);
     HDC dummy_dc = GetDC(dummy_window);

    /* Makes a pixel format for win32 fix for the current platform (I think) */
    PIXELFORMATDESCRIPTOR pfd = {
        .nSize = sizeof(pfd),
        .nVersion = 1,
        .iPixelType = PFD_TYPE_RGBA,
        .dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        .cColorBits = 32,
        .cAlphaBits = 8,
        .iLayerType = PFD_MAIN_PLANE,
        .cDepthBits = 24,
        .cStencilBits = 8,
    };

    /* Gets a pixel format fir the dummy wgl context */
    int pixel_format = ChoosePixelFormat(dummy_dc, &pfd);
    SetPixelFormat(dummy_dc, pixel_format, &pfd);
   
   /* Creates and enable a new dummy webgl context */
    HGLRC dummy_context = wglCreateContext(dummy_dc);
    wglMakeCurrent(dummy_dc, dummy_context);
    /* Loads the necessary functions for making a proper wgl context from the dummy comtext*/
    wglCreateContextAttribsARB = wglGetProcAddress(
        "wglCreateContextAttribsARB");
    wglChoosePixelFormatARB = wglGetProcAddress(
        "wglChoosePixelFormatARB");

    wglMakeCurrent(dummy_dc, 0);
    wglDeleteContext(dummy_context);
    ReleaseDC(dummy_window, dummy_dc);
    DestroyWindow(dummy_window);
    int pixel_format_attribs[] = {
        WGL_DRAW_TO_WINDOW_ARB,     GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB,     GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB,      GL_TRUE,
        WGL_ACCELERATION_ARB,       WGL_FULL_ACCELERATION_ARB,
        WGL_PIXEL_TYPE_ARB,         WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB,         32,
        WGL_DEPTH_BITS_ARB,         24,
        WGL_STENCIL_BITS_ARB,       8,
        0
    };
    /* Asks a proper pixel format to the dummy wgl ctx */
    UINT num_formats;
    wglChoosePixelFormatARB(real_dc, pixel_format_attribs, 0, 1, &pixel_format, &num_formats);
    
    /* Sets the pixel format now that we get it*/
    DescribePixelFormat(real_dc, pixel_format, sizeof(pfd), &pfd);
    SetPixelFormat(real_dc, pixel_format, &pfd);

    /* Specify that we want to create an OpenGL 3.3 core profile context */
    int gl33_attribs[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
        WGL_CONTEXT_MINOR_VERSION_ARB, 3,
        WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0,
    };
    /* Creates a wgl context */
    display->context = wglCreateContextAttribsARB(real_dc, 0, gl33_attribs);
    wglMakeCurrent(real_dc, display->context);
And the emscripten:

    display->context = emscripten_webgl_create_context("canvas", 0); /* creates the webgl context */
    emscripten_webgl_make_context_current(display->context); /* makes the context current */
    emscripten_webgl_make_context_current(display->context); /* makes the context current; */
    /* sets the callbacks */
    emscripten_set_keydown_callback("canvas", display, 1, judd_keydown_handler);
    emscripten_set_keyup_callback("canvas", display, 1, judd_keyup_handler);
    emscripten_set_mousemove_callback("canvas", display, 1, judd_mouse_move_handler);
    emscripten_set_mousedown_callback("canvas", display, 1, judd_mouse_down_handler);
    emscripten_set_mouseup_callback("canvas", display, 1, judd_mouse_up_handler);
    display->w = w;
    display->h = h;
Now let's implement the `judd_update_display`

    void judd_update_display(judd_display_t *display){
       int i;
       for(i = 0; i < 256; i++){
           if(display->keys[i] == JUDD_KEY_RELEASED) display->JUDD_KEY_UP
           if(display->keys[i] == JUDD_KEY_PRESSED) display->JUDD_KEY_DOWN
        }
        #ifdef __linux__
        
        #endif
        #ifdef _WIN32
        
        #endif
        #ifdef __EMSCRIPTEN__
        
        #endif
    }

Let's do the linux part:

    while (XPending(display->display)) { /* Keep the display openned and say if there's some event */
        XEvent event;
        char k;
        XNextEvent(display->display, &event); /* Get next event */
        switch (event.type) {
            case KeyPress:
                k = XLookupKeysym(&event.xkey, 0); // Get XK_{key_pressed} */
                if(k - XK_a < 26) k = XK_A + (k - XK_a); /* Translate it to the uppercase if is lower (We don't differenciate it here */
                display->keys[k] = JUDD_KEY_PRESSED;
            break;
            case KeyRelease:
                k = XLookupKeysym(&event.xkey, 0); /* Get XK_{key_pressed} */
                if(k - XK_a < 26) k = XK_A + (k - XK_a); /* Translate it to the uppercase if is lower (We don't differenciate it here */
                display->keys[k] = JUDD_KEY_RELEASED;
            break;
            case ButtonPress:
                switch(event.xbutton.button){
                    case Button1:
                        display->mouse_lbutton = JUDD_KEY_PRESSED;
                    break;
                    case Button3:
                        display->mouse_rbutton = JUDD_KEY_PRESSED;               
                    break;
                    default:
                    break;
            }
            break;
            case ButtonRelease:
                switch(event.xbutton.button){
                    case Button1:
                        display->mouse_lbutton = JUDD_KEY_RELEASED;
                    break;
                    case Button3:
                        display->mouse_rbutton = JUDD_KEY_RELEASED;               
                    break;
                    default:
                    break;
            }
            break;
            case MotionNotify:
                display->mouse_x = event.xmotion.x;
            break;
            case ClientMessage:
                wmDeleteMessage = XInternAtom(display->display, "WM_DELETE_WINDOW", False);
                if (event.xclient.data.l[0] == wmDeleteMessage)
                    display->closed = 1;
            break;
       }
    }
    glXSwapBuffers(display->display, display->window);
    


And the windows:

    MSG msg;
    while (PeekMessageA(&msg, display->window, 0, 0, PM>
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
        switch(msg.message){
            case WM_KEYDOWN:
                display->keys[msg.wParam] = JUDD_KEY_PRESSED
            case WM_KEYUP:
                display->keys[msg.wParam] = JUDD_KEY_RELEASED
            break;
            case WM_LBUTTONDOWN:
                display->mouse_lbutton = JUDD_KEY_PRESSED;
            break;
            case WM_LBUTTONUP:
                display->mouse_lbutton = JUDD_KEY_PRESSED;
            break;
            case WM_MOUSEMOVE:
                display->mouse_x = GET_X_LPARAM(msg.lParam);
                display->mouse_y = GET_Y_LPARAM(msg.lParam);
            break;
       }
    }
    display->closed = !IsWindow(display->window);
    SwapBuffers(GetDC(display->window));

See that we implemented the emscripten key dow/key up arrays and mouse variables in the create window function.


And the last function, `judd_display_close`:

    void judd_display_close(judd_display_t *display){
        free(display->name);
        #ifdef __linux__
            XDestroyWindow(display->display, display->window);
        #endif
        #ifdef __WIN32
            DestroyWindow(display->window);
        #endif
    }
