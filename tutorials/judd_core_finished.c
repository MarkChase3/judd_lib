#define JUDD_CORE_IMPL
#ifndef JUDD_CORE_H
#define JUDD_CORE_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#ifdef __linux__
#include <X11/Xlib.h>
#include <GL/glx.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>
#include <X11/Xatom.h>
#endif
#ifdef __WIN32__
#include <windows.h>
#include <windowsx.h>
#include <GL/gl.h>
#include <GL/wgl.h>
#endif
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#include <emscripten.h>
#include <emscripten/html5.h>
#include <GLES2/gl2.h>
#endif

typedef struct JUDD_DISPLAY_STRUCT {
    char keys[256];
    char *name;
    char closed;
    char full;
    int mouse_x;
    int mouse_y;
    char mouse_lbutton;
    char mouse_mbutton;
    char mouse_rbutton;
    #ifdef __linux__
    Window window;
    Display *display;
    // Surface *surface;
    int screen;
    GC graphics_context;
    GLXContext glx_context;
    #endif
    #ifdef _WIN32
    HWND window;
    HGLRC context;
    #endif
    #ifdef __EMSCRIPTEN__
    int w, h;
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context;
    #endif
} judd_display_t;

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
JUDD_KEY_CNTRL = XK_Control_L, JUDD_KEY_BAKCSPACE = XK_BackSpace,
};
#endif
#ifdef _WIN32
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
JUDD_KEY_SPACE = VK_SPACE, JUDD_KEY_ENTER = VK_RETURN, JUDD_KEY_SHIFT = VK_LSHIFT,
JUDD_KEY_CNTRL = VK_LCONTROL, JUDD_KEY_BAKCSPACE = VK_BACK,
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

judd_display_t *judd_create_display(int w, int h, char *name); /* create a window and put platform dependent stuff on that (with endifs of course) */
void judd_set_display_name(judd_display_t *display, char *value);
void judd_set_display_fullscreen(judd_display_t *display, char value);
void judd_update_display(judd_display_t *display); /* Update the display with platform dependent stuff */
void judd_close_display(judd_display_t *display); /* Close the display and the platform dependent stuff */

#endif

#ifdef JUDD_CORE_IMPL
#ifdef __EMSCRIPTEN__
EM_BOOL judd_keydown_handler(int eventType, const EmscriptenKeyboardEvent *keyEvent, void *userData) {
  ((judd_display_t*)userData)->keys[keyEvent->keyCode] = JUDD_KEY_PRESSED;
  return 0;
}

EM_BOOL judd_keyup_handler(int eventType, const EmscriptenKeyboardEvent *keyEvent, void *userData) {
  ((judd_display_t*)userData)->keys[keyEvent->keyCode] = JUDD_KEY_RELEASED;
  return 0;
}
EM_BOOL judd_window_resized_callback(int eventType, const void *reserved, void *userData){
	return 1;
}
EM_BOOL judd_mouse_move_handler(int eventType, const EmscriptenMouseEvent *e, void *userData){
    ((judd_display_t*)userData)->mouse_x = e->clientX;
    ((judd_display_t*)userData)->mouse_y = e->clientY;
    return 1;
}
EM_BOOL judd_mouse_down_handler(int eventType, const EmscriptenMouseEvent *e, void *userData){
    if(!e->button)((judd_display_t*)userData)->mouse_lbutton = JUDD_KEY_PRESSED;
    if(e->button==1)((judd_display_t*)userData)->mouse_mbutton = JUDD_KEY_PRESSED;
    if(e->button==2)((judd_display_t*)userData)->mouse_rbutton = JUDD_KEY_PRESSED;
    return 1;
}
EM_BOOL judd_mouse_up_handler(int eventType, const EmscriptenMouseEvent *e, void *userData){
    if(!e->button)((judd_display_t*)userData)->mouse_lbutton = JUDD_KEY_RELEASED;
    if(e->button==1)((judd_display_t*)userData)->mouse_mbutton = JUDD_KEY_RELEASED;
    if(e->button==2)((judd_display_t*)userData)->mouse_rbutton = JUDD_KEY_RELEASED;
    return 1;
}
#endif
judd_display_t *judd_create_display( int w, int h, char *name){
    judd_display_t *display = malloc(sizeof(judd_display_t));
    display->full = 0;
    display->closed = 0;
    display->name = malloc(strlen(name) * sizeof(char));
    strcpy(display->name, name);
    #ifdef __linux__
    display->display = XOpenDisplay(NULL); /* Opens a display */
    display->screen = XDefaultScreen(display->display); /* Get's the default screen */
    display->window = XCreateSimpleWindow(display->display, RootWindow(display->display, display->screen), 10, 10, w, h, 1, BlackPixel(display->display, display->screen), XWhitePixel(display->display, display->screen)); // select window input types
    // display->surface = XCreateSurface(display->display, display->window);
    XSelectInput(display->display, display->window, ExposureMask | PointerMotionMask | ButtonPressMask | ButtonReleaseMask | KeyPressMask | KeyReleaseMask); /* Select the window types */
    XMapWindow(display->display, display->window); /* Join the display and the window */
    XStoreName(display->display, display->window, display->name);
    XFlush(display->display);
    int nelements;
    GLXFBConfig *fbc = glXChooseFBConfig(display->display, display->screen, 0, &nelements);
    PFNGLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB = (PFNGLXCREATECONTEXTATTRIBSARBPROC) glXGetProcAddress((const GLubyte*)"glXCreateContextAttribsARB");
    int attribs[] = {
		GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
		GLX_CONTEXT_MINOR_VERSION_ARB, 0,
	0};
    GLXContext ctx = glXCreateContextAttribsARB(display->display, *fbc, 0, 1, attribs);
	glXMakeCurrent (display->display, display->window, ctx);
    Atom wmDeleteMessage = XInternAtom(display->display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display->display, display->window, &wmDeleteMessage, 1);
    #endif
    #ifdef _WIN32
    /* The windows code is very extensive (100 lines). If you havea smaller version or can refactorize this to be smaller, please open a pull request */
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
    #endif
    #ifdef __EMSCRIPTEN__
    EmscriptenWebGLContextAttributes attrs;
    emscripten_webgl_init_context_attributes(&attrs); /* Initialize the context attributes*/
    attrs.majorVersion = 2;
    display->context = emscripten_webgl_create_context("canvas", &attrs); /* creates the context  */
    emscripten_webgl_make_context_current(display->context); /* makes the context current; */
    emscripten_set_keydown_callback("canvas", display, 1, judd_keydown_handler);
    emscripten_set_keyup_callback("canvas", display, 1, judd_keyup_handler);
    emscripten_set_mousemove_callback("canvas", display, 1, judd_mouse_move_handler);
    emscripten_set_mousedown_callback("canvas", display, 1, judd_mouse_down_handler);
    emscripten_set_mouseup_callback("canvas", display, 1, judd_mouse_up_handler);
    display->w = w;
    display->h = h;
    #endif
    return display;
}

void judd_set_display_name(judd_display_t *display, char* value){
    strcpy(display->name, value);
    #ifdef __linux__
    XStoreName(display->display, display->window, display->name);
    #endif
    #ifdef _WIN32
    SetWindowTextA(display->window, value);
    #endif
}
void judd_set_display_fullscreen(judd_display_t *display, char value){
    display->full = value;
    #ifdef __EMSCRIPTEN__
    if(value){
        EmscriptenFullscreenStrategy strategy;
        strategy.scaleMode = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_STDDEF;
        strategy.filteringMode = EMSCRIPTEN_FULLSCREEN_FILTERING_DEFAULT;
        strategy.canvasResizedCallback = judd_window_resized_callback;
        strategy.canvasResizedCallbackUserData = display;
        emscripten_enter_soft_fullscreen("canvas", &strategy);
    } else {
        emscripten_set_element_css_size("canvas", display->w, display->h);
    }
    #endif
    #ifdef _WIN32
    /* I confess I don't know how this work, but it puts the window on fullscreen */
    if (GetWindowLongPtr(display->window, GWL_STYLE) & WS_POPUP)
    {
        SetWindowLongPtr(display->window, GWL_STYLE, WS_VISIBLE | WS_OVERLAPPEDWINDOW);
        SetWindowPos(display->window, NULL, 0, 0, 600, 400, SWP_FRAMECHANGED);
    }
    else
    {
        int w = GetSystemMetrics(SM_CXSCREEN);
        int h = GetSystemMetrics(SM_CYSCREEN);
        SetWindowLongPtr(display->window, GWL_STYLE, WS_VISIBLE | WS_POPUP);
        SetWindowPos(display->window, HWND_TOP, 0, 0, w, h, SWP_FRAMECHANGED);
    }
    #endif
    #ifdef __linux__
    /* I also don't know how this works */
    Atom wm_state = XInternAtom (display->display, "_NET_WM_STATE", 1);
    Atom wm_fullscreen = XInternAtom (display->display, "_NET_WM_STATE_FULLSCREEN", 1);
    XEvent xev;
    memset(&xev, 0, sizeof(xev));
    xev.type = ClientMessage;
    xev.xclient.window = display->window;
    xev.xclient.message_type = wm_state;
    xev.xclient.format = 32;
    xev.xclient.data.l[1] = wm_fullscreen;
    xev.xclient.data.l[2] = 0;
    if(value){
        xev.xclient.data.l[0] = 1;
        XSendEvent(display->display, DefaultRootWindow(display->display), False, SubstructureRedirectMask | SubstructureNotifyMask, &xev);
    } else {
        xev.xclient.data.l[0] = 0;
        XSendEvent(display->display, DefaultRootWindow(display->display), False, SubstructureRedirectMask | SubstructureNotifyMask, &xev);
    }
    #endif
}

void judd_update_display(judd_display_t *display){
    int i;
    for(i = 0; i < 256; i++){
        if(display->keys[i] == JUDD_KEY_RELEASED) display->keys[i] = JUDD_KEY_UP; /* If a key was released on the past frame, now it's up */
        if(display->keys[i] == JUDD_KEY_PRESSED) display->keys[i] = JUDD_KEY_DOWN; /* If a key was pressed on the past frame, now it's down */

    }
    if(display->mouse_rbutton == JUDD_KEY_RELEASED) display->mouse_rbutton = JUDD_KEY_UP;
    if(display->mouse_rbutton == JUDD_KEY_PRESSED) display->mouse_rbutton = JUDD_KEY_DOWN;
    if(display->mouse_lbutton == JUDD_KEY_RELEASED) display->mouse_lbutton = JUDD_KEY_UP;
    if(display->mouse_lbutton == JUDD_KEY_PRESSED) display->mouse_lbutton = JUDD_KEY_DOWN;
    #ifdef __linux__
    unsigned int mask;
    Window root_window;
    Atom wmDeleteMessage;
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
    #endif
    #ifdef _WIN32
    MSG msg;
    while (PeekMessageA(&msg, display->window, 0, 0, PM_REMOVE)) { /* Say if there's some event on the queue */
       TranslateMessage(&msg);
       DispatchMessageA(&msg);
       switch(msg.message){
            case WM_KEYDOWN: /* If pressed a key */
                display->keys[msg.wParam] = JUDD_KEY_PRESSED;
            break;
            case WM_KEYUP: /* If released a key */
                display->keys[msg.wParam] = JUDD_KEY_RELEASED;
            break;
            case WM_LBUTTONDOWN:
                display->mouse_lbutton = JUDD_KEY_PRESSED;
            break;
            case WM_LBUTTONUP:
                display->mouse_lbutton = JUDD_KEY_RELEASED;
            break;
            case WM_MOUSEMOVE:
                display->mouse_x = GET_X_LPARAM(msg.lParam);
                display->mouse_y = GET_Y_LPARAM(msg.lParam);
            break;
       }
    }
    display->closed = !IsWindow(display->window);
    SwapBuffers(GetDC(display->window));
    #endif
    #ifdef __EMSCRIPTEN__
    emscripten_sleep(10);
    #endif
}
void judd_display_close(judd_display_t *display){
    free(display->name);
    #ifdef __linux__
          XDestroyWindow(display->display, display->window);
    #endif
    #ifdef __WIN32
          DestroyWindow(display->window);
    #endif
}
#endif
int main(){
    float r, g ,b;
    judd_display_t *display = judd_create_display(0, 0, 512, 512, "Name For The Display");
    while(!display->closed){
        if(display->keys[JUDD_KEY_F] == JUDD_KEY_PRESSED){
            judd_set_display_fullscreen(display, !display->full);
        }
        if(display->keys[JUDD_KEY_R] == JUDD_KEY_PRESSED){
            r = 1.0;
            g = 0.0;
            b = 0.0;
            judd_set_display_name(display, "red display");
        }
        if(display->keys[JUDD_KEY_G] == JUDD_KEY_PRESSED){
            r = 0.0;
            g = 1.0;
            b = 0.0;
            judd_set_display_name(display, "green display");
        }
        if(display->keys[JUDD_KEY_B] == JUDD_KEY_PRESSED){
            r = 0.0;
            g = 0.0;
            b = 1.0;
            judd_set_display_name(display, "blue display");
        }
        glClearColor(r + (float)display->mouse_x/512.0, g + (float)display->mouse_x/512.0, b + (float)display->mouse_x/512.0, 1.0);
        if(display->mouse_lbutton == JUDD_KEY_DOWN)glClear(GL_COLOR_BUFFER_BIT);
        judd_update_display(display);
    }
    printf("Exiting with success!\n");
    return 0;
}
