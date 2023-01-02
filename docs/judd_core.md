# JUDD_CORE

## Introduction

JUDD_CORE is a judd module that creates a window and a opengl context and manages them.
This documentation has 3 parts: This, the introduction, an getting started and a manual.

## Gettig started

Firstly, let's include `judd_core`:

    #define JUDD_CORE_IMPL
    #include "judd_core.h"

See that we need to define `JUDD_CORE_IMPL` to have an implementation, but that must be just on the first include. If you project has multiple C files that include judd_core.h, you must define `JUDD_CORE_IMPL` just on one.

Let's make a main function now:
    
    int main(){
        judd_display_t *display = judd_create_display(640, 360, "My APP");
        while(!display->closed){
            judd_update_display(display);
        }
        judd_display_close(display);
    }
    
Let's just clear the screen according with inputs, 'cause that's the best we can do without having to load all gl functions with something like glad.
    
    /* Before mainloop */
    float r, g, b;
    /* On mainloop: */
    if(display->keys[JUDD_KEY_R] == JUDD_KEY_PRESSED && display->mouse_lbutton){
        /* If you pressed the r key and pressed the left mouse button at the same time */
        r = 1.0;
    }
    if(display->keys
        [JUDD_KEY_R] == JUDD_KEY_PRESSED && display->mouse_rbutton){
        /* If you pressed the r key and pressed the right mouse button at the same time */
        r = 0.0;
    }
    /* Repeat it for g and b */
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BIT);

It must add full red/green/blue to the image when you press 'r'/'g'/'b' and left click and remove all the red/green/blue from the image when pressing the corresponding buttons with the right click.

So clicking 'r' + left and 'b' + left, must do a pink screen.

Full code:
    
    #define JUDD_CORE_IMPL
    #include "judd_core.h"
    int main(){
        judd_display_t *display = judd_create_display(640, 360, "My APP");
        float r, g, b;
        while(!display->closed){
            if(display->keys[JUDD_KEY_R] == JUDD_KEY_PRESSED && display->mouse_lbutton) r = 1.0;
            if(display->keys
        [JUDD_KEY_R] == JUDD_KEY_PRESSED && display->mouse_rbutton)r = 0.0;
            if(display->keys[JUDD_KEY_G] == JUDD_KEY_PRESSED && display->mouse_lbutton) r = 1.0;
            if(display->keys
        [JUDD_KEY_G] == JUDD_KEY_PRESSED && display->mouse_rbutton)g = 0.0;
            if(display->keys[JUDD_KEY_B] == JUDD_KEY_PRESSED && display->mouse_lbutton) b = 1.0;
            if(display->keys
        [JUDD_KEY_B] == JUDD_KEY_PRESSED && display->mouse_rbutton)b = 0.0;
    /* Repeat it for g and b */
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BIT);
            judd_update_display(display);
        }
        judd_display_close(display);
    }
