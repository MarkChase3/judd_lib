# JUDD_TIME

JUDD_TIME is a judd module that gets time and can do delays. This documentation has 3 parts: This, the introduction, an getting started and a manual.

## Getting Started

You can use this for making animations easily!. For help us in this, I will use judd_draw, judd_gl_loader, judd_ecs and judd_core, but you can use just the judd_time, something like GLFW and raw C.

### Includes....

    
    #define JUDD_TIME_IMPL
    #include "judd_time.h"
    #define JUDD_ECS_IMPL
    #include "judd_ecs.h"
    #define JUDD_CORE_IMPL
    #include "judd_core.h"
    #include JUDD_GL_LOADER_IMPL
    #define "judd_draw.h"
    #include JUDD_DRAW_IMPL
    #define "judd_draw.h"

    int main(){
    
    }

### Initializing....

    judd_display_t *displ = judd_create_windoww(640, 360, "Time test");
   
If you don't know this, look at  []
