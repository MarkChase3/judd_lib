# JUDD_LIB

## What this is exactly?
This is a library of single header independent modules, that can create big applications when used together or with others APIs.

## Why that name?
Donald Judd was a freaking cool guy, one of the first minimalistic thinkers. As this API is destined to be the simpler as possible, I decided to pay a homage to his work.

## Why C?
Because C is so freaking cool, man.
But really, C is, in my opinion, the cooler language we have.
I already made some projects in C++, js, python and even lua, some were good, some were not, but I always loved and will love C. I am very inspired on sokol, raylib and pico_headers to do this.
Another reasons are for learning, recreation and personal use.

## How can I built it?
You don't. Seriously. Everything here is in a single and independent file. No third parties. Nothing of Glad, GLFW, GLM, or similar. So just clone/download this repo and drag and drop the necessary headers onto your project.
Some modules will need a linker flag, but that should already come on your system. Here's an table.

Module name | Flags To Add On Linux | Backend APIs On Linux | Flags To Add on Windows | Backend APIs On Windows | Flags To Add On Emscripten
--|--|--|--|--|--
judd_core |  -lX11 -lGL -lGLX | X11, OpenGL and GLX | -lgid32 -lopengl32 | Win32, OpengGL and WGL | -GL -sASYNCIFY |
judd_gl_loader | -lGL -lGLX | OpenGL and GLX | -lgdi32 -lopengl32 | WGL and OpenGL | Not tested
judd_draw | -lGL | OpenGL | -lgdi32 -lopengl32 | OpenGL | Not tested

## Some examples
For compactness, here's a little walktrough over all the modules by once.

### Including

Just define ````*JUDD_MOUDLE*_IMPL```` and include the files

    #define JUDD_CORE_IMPL
    #include "judd_core.h"
    #define JUDD_GL_LOADER_IMPL
    #include "judd_gl_loader.h"
    #define JUDD_DRAW_IMPL
    #include "judd_draw.h"
    #define JUDD_IMG_LOADER_IMPL
    #include "judd_img_loader.h"
    #define JUDD_ECS_IMPL
    #include "judd_dcs.h"

### Initializing
Before drawing images, we need to load OpenGL functions. Before loading OpenGL functions, we need to create a valid OpenGL context. So in the end, we have this:

    int main(){
        judd_display_t *displ = judd_create_display(640, 360, "Cool Name");
        judd_load_gl()
        .
        .
        .
        judd_close_display(displ);
    }
    
judd_create_display creates the OpenGL context and judd_load_gl load the OpenGL functions.

### Entities
The judd_ecs module is preety simple but powerful. With it, you scale up the speed of development fast. Let's create an ecs first.

    int nentities = 64;
    int ncompoennts = 64;
    int nsystems = 64;
    judd_ecs_t *ecs = judd_create_ecs(nentities, ncomponents, nsystems);
    judd_entity_t *player = judd_add_entity_to_ecs(ecs, 0, "player");
    judd_entity_t *enemie = judd_add_entity_to_ecs(ecs, 0, "enemie");

The second parameter of ´´´´ judd_add_entity_to_ecs´´´´ specify if the entity created is sleeping. The third is the entity id.

### Components
Let's create an triangle, rectangle, and texture components:
    
    typedef struct Rectangle {
        int x0, x1, y0, y1;
    }
    typedef struct Triangle {
        int x0, x1, x2, y0, y1, y2;
    }
    typedef judd_texture_t* Texture;
    judd_component_pool_t *rect = judd_add_component_pool_to_ecs(ecs, sizeof(Rectangle), "rect");
    judd_component_pool_t *triangle = judd_add_component_pool_to_ecs(ecs, sizeof(Triangle), "triangle");
    judd_component_pool_t *texture = judd_add_component_to_ecs(ecs, sizeof(Texture), "texture");
 
The code is self-documenting, but I am going to explain it anyway. You need to create a type for each component pool, and then add it to the ecs, by calling ´´´´judd_add_component_pool_to_ecs´´´´, passing the ecs, the size of each component from the pool and the component id.

### Entities and Components

    judd_add_component_to_entity(ecs, "player", "rect");
    judd_add_component_to_entity(ecs, "player", "texture");
    judd_add_component_to_entity(ecs, "enemie", "triangle");
    judd_add_component_to_entity(ecs, "enemie", "texture");

You must pass the an entity id to ´´´´judd_add_component_to_entity´´´´ and after that a component poop id in order to add components to entities.

    *judd_get_component_from_entity(ecs, "player", "rect") = (Rectangle){.x0 = 100, x1 = 200, .y0 = 100, y1 = 200};
    *judd_get_component_from_entity(ecs, "player", "texture") = judd_create_texture(judd_load_bmp(judd), 100, 69);
    
As we are on C, we don't get references from C++, so ´´´´judd_get_component´´´´ returns a pointer that must be unreferenced to get the actual data. It's parameters are th same from judd_get_component_from_entity

### Systems
Here is where the judd_ecs logic comes. We can create functions that are called one time for each entity that has certain components, those functions are called systems. Look:

     void update_texture_rect(judd_ecs_t *ecs, judd_entity_t *ent){
         char *name = judd_get_entity_name(ecs, ent);
         judd_texture_t *texture = judd_get_component_from_entity(ecs, name, "texture");
         Rectangle rect = judd_get_component_from_entity(ecs, name, "rect");
         judd_draw_rect(JUDD_DTYPE_TEX, rec.x0, rect.y0, 0, 0, rect.x1, rect.y0, texture->w, 0, rect.x1, rect.y1, texture->w, texture->h, rect.x0, rect.y1, 0, texture->h, tex);
    }

Now we add the system to the ecs:
    
    judd_system_t *rect_tex_system = judd_add_system_to_ecs(ecs, update_map, (judd_entity_t){.components = (1 << (rect - ecs->pool)) & (1 << (triangle - ecs->pools))});


### Mainloop
Here we update all the modules that need to be updated:

    while(!displ->closed){
        .
        .
        .
        judd_update_ecs(ecs);
        judd_update_display();
    }

/* TODO: MOVEMENT_PLAYER AND MOVEMENT_ENEMIE SYSTEMS AND COMPONENTS */
## What are the modules?

The following are planned to the final version:

Module Name | Explanation | Current Version | Docs level
-------|--------|------|-----
judd_core | Opengl context creation and window mangement | 1.0 | High
judd_draw | Drawing operations on a opengl context | 1.0 | Few
judd_gl_load | OpengGL functions loading on few lines | 0.5 | Medium (single funtion)
judd_img_load | Image files loading | 0.5 | Medium (also single function)
judd_audio | To play audio files | WIP | WIP
judd_audio_loader | To load audio | 0.5 | Medium
judd_time | To manage time | 1.0| Medium
judd_ecs | Entity component system | 0.75 | Few
judd_json | Json Loading | WIP | WIP
judd_physics | To handle physics | WIP | WIP
judd_math | Util math | WIP | WIP
judd_net | Networking API | WIP | WIP
judd_string | String Handling API | WIP | WIP
judd_containers | Some Containers implementations | WIP | WIP
judd_procedural | Perlin noise and others procedural like algorithms| WIP | WIP
judd_pathfinding | Astar and other pathfinding algorithms| WIP | WIP

0.5 versions are usbale, but can't do every thing I expected. 1.0 versions are good and you can do a good app with them easily, but probably will have more updates. 0.75 is a mid-term.

Abundant documentation is when I made an walktrough on the code, a getting started, a manual and some examples. High is when it's missing 1. Medium is when the module is very simple or miss 2 or the doc types. Few miss 3 or more.

I have sttrugled a few on a png decoder, because I wanted to do it in a single function, don't ask me why. Now I will throw this away and I am going to work more hardly on judd_audio, judd_json and some documentation. Expect to have most work done until end of january.
