#define JUDD_CORE_IMPL
#include "../include/judd_core.h"
int main(){
    judd_display_t *display = judd_create_display(640, 360, "My APP");
    float r, g, b;
    while(!display->closed){
        if(display->keys[JUDD_KEY_R] == JUDD_KEY_PRESSED && display->mouse_lbutton) r = 1.0;
        if(display->keys
    [JUDD_KEY_R] == JUDD_KEY_PRESSED && display->mouse_rbutton)r = 0.0;
        if(display->keys[JUDD_KEY_G] == JUDD_KEY_PRESSED && display->mouse_lbutton) g = 1.0;
        if(display->keys
    [JUDD_KEY_G] == JUDD_KEY_PRESSED && display->mouse_rbutton)g = 0.0;
        if(display->keys[JUDD_KEY_B] == JUDD_KEY_PRESSED && display->mouse_lbutton) b = 1.0;
        if(display->keys
    [JUDD_KEY_B] == JUDD_KEY_PRESSED && display->mouse_rbutton)b = 0.0;
        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        judd_update_display(display);
    }
    judd_close_display(display);
}
