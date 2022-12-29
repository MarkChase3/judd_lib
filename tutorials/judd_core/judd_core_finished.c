#define JUDD_CORE_IMPL
#ifndef JUDD_CORE_H
#define JUDD_CORE_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#ifdef __linux__
#include <X11/Xlib.h>
#include <GL/glx.h>
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
judd_event_t judd_get_display_event(judd_display_t *display, int property);
void judd_set_display_event(judd_display_t *display, int property, judd_event_t event);

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
    JUDD_DISPLAY_EVENT_CLOSE,
    JUDD_DISPLAY_EVENT_MINIMIZE,
    JUDD_DISPLAY_EVENT_MAXIMIZE,
    JUDD_DISPLAY_EVENT_FULL
};

judd_display_t *judd_create_display(int x, int y, int w, int h, char *name); /* create a window and put platform dependent stuff on that (with endifs of course) */
void judd_change_display_property(judd_display_t *display, int property, int *value); /* Set a display porperty  (like name, position on screen, width, or even events */
int judd_get_display_property(judd_display_t *display, int property);
void judd_update_display(judd_display_t *display); /* Update the display with platform dependent stuff */
void judd_close_display(judd_display_t *display); /* Close the display and the platform dependent stuff */

#endif

#ifdef JUDD_CORE_IMPL
typedef struct JUDD_DISPLAY_STRUCT {
    int w;
    int h;
    int x;
    int y;
    char *name;
    char resized;
    char closed;
    char minimized;
    char maximized;
    char full;
    judd_event_t event_resize;
    judd_event_t event_close;
    judd_event_t event_full;
    judd_event_t event_maxmize;
    judd_event_t event_minimize;
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
    display->name = malloc(strlen(name) * sizeof(char));
    strcpy(display->name, name);
    #ifdef __linux__
    display->display = XOpenDisplay(NULL); // Opens a display
    display->screen = XDefaultScreen(display->display); // Get's the default screen
    display->window = XCreateSimpleWindow(display->display, RootWindow(display->display, display->screen), 10, 10, w, h, 1, BlackPixel(display->display, display->screen), XWhitePixel(display->display, display->screen)); // select window input types
    XSelectInput(display->display, display->window, ExposureMask | KeyPressMask); // Select the window types
    XMapWindow(display->display, display->window); // Join the display and the window
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
    }; // Creates a proper win32 window class
    RegisterClassA(&wc); // register the window class
    display->window = CreateWindowExA(0, name, name, WS_OVERLAPPEDWINDOW|WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, w, h, NULL, NULL, GetModuleHandle(NULL), NULL); // create the real window
    #endif
    #ifdef __EMSCRIPTEN__
    display->context = emscripten_webgl_create_context("canvas", 0); // creates the context
    emscripten_webgl_make_context_current(display->context); // makes the context current;
    #endif
    return display;
}

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

int judd_get_display_property(judd_display_t *display, int property){
    if(property == JUDD_DISPLAY_W) return display->w;
    if(property == JUDD_DISPLAY_H) return display->h;
    if(property == JUDD_DISPLAY_X) return display->x;
    if(property == JUDD_DISPLAY_Y) return display->y;
    if(property == JUDD_DISPLAY_RESIZED) return display->resized;
    if(property == JUDD_DISPLAY_CLOSED) return display->closed;
    if(property == JUDD_DISPLAY_MINIMIZED) return display->minimized;
    if(property == JUDD_DISPLAY_FULL) return display->full;
}
judd_event_t judd_get_display_event(judd_display_t *display, int property){
    if(property == JUDD_DISPLAY_EVENT_RESIZE) return display->event_resize;
    if(property == JUDD_DISPLAY_EVENT_CLOSE) return display->event_close;
    if(property == JUDD_DISPLAY_EVENT_MINIMIZE) return display->event_minimize;
    if(property == JUDD_DISPLAY_EVENT_MAXIMIZE) return display->event_maxmize;
}
void judd_set_display_event(judd_display_t *display, int property, judd_event_t event){
    if(property == JUDD_DISPLAY_EVENT_RESIZE) display->event_resize = event;
    if(property == JUDD_DISPLAY_EVENT_CLOSE) display->event_close = event;
    if(property == JUDD_DISPLAY_EVENT_MINIMIZE) display->event_minimize = event;
    if(property == JUDD_DISPLAY_EVENT_MAXIMIZE) display->event_maxmize = event;
}
#endif
int main(){
    judd_display_t *display = judd_create_display(0, 0, 512, 512, "Name For The Display");
    printf("%lld", judd_get_display_property(display, JUDD_DISPLAY_W));
}
