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
   
If you don't know this, look at  [judd_core](https://github.com/MarkChase3/judd_lib/blob/main/docs/judd_core.md)

    judd_load_gl();
    
This simply is defined on judd_gl_loader and, guess, loads opengl functions.

     judd_ecs_t *ecs = judd_create_ecs(64, 64, 64);
     judd_entity_t *guy = judd_add_entity_to_ecs(ecs, 0, "guy");
     judd_component_pool_t *square = judd_add_component_pool_to_ecs(ecs, sizeof(strut {int x0, x1, y0, y1;}), "square");
     judd_component_pool_t *speed = judd_add_component_pool_to_ecs(ecs, sizeof(strut {int x, y;}), "speed");
     judd_system_t *anim_system = judd_add_system_to_ecs(ecs, update_anim, (judd_entity_t){.components = 1 | 2});
     judd_add_component_to_entity(ecs, "gyuy", "square");
     *judd_get_component_from_entity(ecs, "guy", "square") = (struct{int x0, x1, y0, y1;}){.x0 = 100, .x1 = 150, .y0 = 100, y1 = 150};
### Mainloop

    while(){
        .
        .
        .
        judd_update_display(displ);
    }

Just the basic here, let's animate somethings.

    void animate(judd_ecs_t *ecs, judd_entity_t *ent){
        static int prev = judd_get_time();
        int dt = judd_get_time() - prev;
        prev = judd_get_time();
        char *name = judd_get_entity_name(ent);
        struct{int x0, x1, y0, y1;} rect = judd_get_component_from_entity(ecs, name, "rectangle");
        struct{int x,y;} speed = judd_get_component_from_entity(ecs, name, "speed");
        rect->x0 += speed->x;
        rect->y0 += speed->y;
        rectx.x0 +=
