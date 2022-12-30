
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
#endif
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#include <emscripten.h>
#include <emscripten/html5.h>
#include <GLES2/gl2.h>
#endif

typedef struct JUDD_DISPLAY_STRUCT judd_display_t;
typedef void(*judd_event_t)(judd_display_t *display);

enum {
    JUDD_DISPLAY_W,
    JUDD_DISPLAY_H,
    JUDD_DISPLAY_X,
    JUDD_DISPLAY_Y,
    JUDD_DISPLAY_CLOSED,
    JUDD_DISPLAY_FULL,
};

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
enum {JUDD_KEY_UP, JUDD_KEY_RELEASED, JUDD_KEY_PRESSED, JUDD_KEY_DOWN};

judd_display_t *judd_create_display(int x, int y, int w, int h, char *name); /* create a window and put platform dependent stuff on that (with endifs of course) */
void judd_set_display_property(judd_display_t *display, int property, int value); /* Set a display porperty  (like name, position on screen, width, etc */
int judd_get_display_property(judd_display_t *display, int property); /* Gets a display property */
void judd_update_display(judd_display_t *display); /* Update the display with platform dependent stuff */
char judd_key_check(judd_display_t *display, char key); /* Check the state of a key (Shorthand for getting key property) */
void judd_close_display(judd_display_t *display); /* Close the display and the platform dependent stuff */

#endif

#ifdef JUDD_CORE_IMPL
typedef struct JUDD_DISPLAY_STRUCT {
    int w;
    int h;
    int x;
    int y;
    char keys[256];
    char *name;
    char closed;
    char full;
    #ifdef __linux__
    Window window;
    Display *display;
    int screen;
    GC graphics_context;
    GLXContext glx_context;
    #endif
    #ifdef _WIN32
    HWND window;
    #endif
    #ifdef __EMSCRIPTEN__
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context;
    #endif
} judd_display_t;

judd_display_t *judd_create_display(int x, int y, int w, int h, char *name){
    judd_display_t *display = malloc(sizeof(judd_display_t));
    display->w = w;
    display->h = h;
    display->x = x;
    display->y = y;
    display->full = 0;
    display->closed = 0;
    display->name = malloc(strlen(name) * sizeof(char));
    strcpy(display->name, name);
    #ifdef __linux__
    display->display = XOpenDisplay(NULL); /* Opens a display */
    display->screen = XDefaultScreen(display->display); /* Get's the default screen */
    display->window = XCreateSimpleWindow(display->display, RootWindow(display->display, display->screen), 10, 10, w, h, 1, BlackPixel(display->display, display->screen), XWhitePixel(display->display, display->screen)); // select window input types
    XSelectInput(display->display, display->window, ExposureMask | KeyPressMask); /* Select the window types */
    XMapWindow(display->display, display->window); /* Join the display and the window */
    XStoreName(display->display, display->window, display->name);
    XFlush(display->display);
    #endif
    #ifdef _WIN32
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
    #endif
    #ifdef __EMSCRIPTEN__
    display->context = emscripten_webgl_create_context("canvas", 0); /* creates the context  */
    emscripten_webgl_make_context_current(display->context); /* makes the context current; */
    #endif
    return display;
}

void judd_set_display_property(judd_display_t *display, int property, int value){
    if(property == JUDD_DISPLAY_W) display->w = value;
    if(property == JUDD_DISPLAY_H) display->h = value;
    if(property == JUDD_DISPLAY_X) display->x = value;
    if(property == JUDD_DISPLAY_Y) display->y = value;
    if(property == JUDD_DISPLAY_CLOSED) display->closed = value;
    if(property == JUDD_DISPLAY_FULL){
        display->full = value;
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
        printf("%d\n", value);
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
}

int judd_get_display_property(judd_display_t *display, int property){
    if(property == JUDD_DISPLAY_W) return display->w;
    if(property == JUDD_DISPLAY_H) return display->h;
    if(property == JUDD_DISPLAY_X) return display->x;
    if(property == JUDD_DISPLAY_Y) return display->y;
    if(property == JUDD_DISPLAY_CLOSED) return display->closed;
    if(property == JUDD_DISPLAY_FULL) return display->full;
}
void judd_update_display(judd_display_t *display){
    int i;
    for(i = 0; i < 256; i++){
        if(display->keys[i] == JUDD_KEY_RELEASED) display->keys[i] = JUDD_KEY_UP; /* If a key was released on the past frame, now it's up */
        if(display->keys[i] == JUDD_KEY_PRESSED) display->keys[i] = JUDD_KEY_DOWN; /* If a key was pressed on the past frame, now it's down */

    }
    #ifdef __linux__
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
       }
    }
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
       }
    }
    #endif
}

/* Auto explaning function */
char judd_key_check(judd_display_t *display, char key){
    return display->keys[key];
}
#endif
int main(){
    judd_display_t *display = judd_create_display(0, 0, 512, 512, "Name For The Display");
    while(!judd_get_display_property(display, JUDD_DISPLAY_CLOSED)){
        if(judd_key_check(display, JUDD_KEY_F) == JUDD_KEY_PRESSED){
            judd_set_display_property(display, JUDD_DISPLAY_FULL, !judd_get_display_property(display, JUDD_DISPLAY_FULL));
        }
        judd_update_display(display);
    }
}
