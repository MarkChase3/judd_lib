#ifndef JUDD_ECS_H
#define JUDD_ECS_H
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    uint64_t components;
    uint8_t sleeping;
} judd_entity_t;
typedef struct JUDD_COMPONENT_POOL_STRUCT{
    int size;
    char *pool;
} judd_component_pool_t;

typedef struct JUDD_ECS_STRUCT judd_ecs_t;
typedef struct JUDD_SYSTEM_T {
    void(*fn)(judd_ecs_t* ecs, judd_entity_t *entity);
    judd_entity_t match;
} judd_system_t;

typedef struct JUDD_ECS_STRUCT {
    judd_component_pool_t *pools;
    char **pools_names;
    judd_entity_t *entities;
    char **entities_names;
    judd_system_t **systems;
    int max_entities;
    int max_components;
    int max_systems;
    int n_entities;
    int n_components;
    int n_systems;
} judd_ecs_t;

judd_ecs_t *judd_create_ecs(int max_entities, int max_components, int max_systems);
judd_entity_t *judd_add_entity_to_ecs(judd_ecs_t *ecs, uint8_t sleeping, char *name);
judd_system_t *judd_add_system_to_ecs(judd_ecs_t *ecs, void(*fn)(judd_ecs_t *, judd_entity_t *), judd_entity_t match);
judd_component_pool_t *judd_add_component_pool_to_ecs(judd_ecs_t *ecs, int size, char* name);
judd_entity_t *judd_add_component_to_entity(judd_ecs_t *ecs, char *name, char *pool);
judd_entity_t *judd_get_entity_from_ecs(judd_ecs_t *ecs, char *name);
char *judd_get_entity_name(judd_ecs_t *ecs, judd_entity_t *entity);
char *judd_get_component_from_entity(judd_ecs_t *ecs, char *entity_name, char *pool_name);
judd_entity_t *judd_update_ecs(judd_ecs_t *ecs);
judd_entity_t *judd_remove_component_from_entity(judd_ecs_t *ecs, judd_entity_t *name, char *pool);
void judd_remove_component_pool_from_ecs(judd_ecs_t *ecs, char *pool_name);
void judd_remove_entity(judd_ecs_t *ecs, char *name);
void judd_end_ecs(judd_ecs_t *ecs);
#endif
#ifdef JUDD_ECS_IMPL
judd_ecs_t *judd_create_ecs(int max_entities, int max_components, int max_systems){
    judd_ecs_t *ecs = malloc(sizeof(judd_ecs_t));
    *ecs = (judd_ecs_t){
           .pools = malloc(max_components * sizeof(judd_component_pool_t)),
           .pools_names = malloc(max_components * sizeof(char*)),
           .entities = malloc(max_entities * sizeof(judd_entity_t)),
           .entities_names = malloc(max_entities * sizeof(char*)),
           .systems = malloc(max_systems * sizeof(judd_system_t*)),
           .max_entities = max_entities,
           .max_components = max_components,
           .max_systems = max_systems,
           .n_entities = 0,
           .n_components = 0,
           .n_systems = 0
    };
    return ecs;
}
judd_system_t *judd_add_system_to_ecs(judd_ecs_t *ecs, void(*fn)(judd_ecs_t *, judd_entity_t*), judd_entity_t match){
    judd_system_t *sys = malloc(sizeof(judd_system_t));
    *sys = (judd_system_t){.fn = fn, .match = match};
    ecs->systems[ecs->n_systems] = sys;
    ecs->n_systems++;
    return sys;
}
judd_entity_t *judd_add_entity_to_ecs(judd_ecs_t *ecs, uint8_t sleeping, char *name){
    ecs->entities[ecs->n_entities] = (judd_entity_t){.components = 0, .sleeping = sleeping};
    ecs->entities_names[ecs->n_entities] = malloc(sizeof(char) * 32);
    strcpy(ecs->entities_names[ecs->n_entities], name);
    ecs->n_entities++;
    return &(ecs->entities[ecs->n_entities-1]);
}
judd_component_pool_t *judd_add_component_pool_to_ecs(judd_ecs_t *ecs, int size, char *name){
    ecs->pools[ecs->n_components] = (judd_component_pool_t){.size = size, .pool = malloc(ecs->n_entities * size)};
    ecs->pools_names[ecs->n_components] = malloc(32 * sizeof(char));
    strcpy(ecs->pools_names[ecs->n_components], name);
    ecs->n_components++;
    return &(ecs->pools[ecs->n_components-1]);
}
judd_entity_t *judd_add_component_to_entity(judd_ecs_t *ecs, char *entity_name, char *pool_name){
    int i;
    judd_entity_t *entity;
    for(i = 0; i < ecs->n_entities; i++)
        if(strcmp(ecs->entities_names[i], entity_name) == 0)
            entity = ecs->entities+i;
    judd_component_pool_t *pool;
    for(i = 0; i < ecs->n_components; i++)
        if(strcmp(ecs->pools_names[i], pool_name) == 0)
            pool = ecs->pools+i;
    entity->components = (1 << (pool - ecs->pools)) | entity->components;
}
char *judd_get_entity_name(judd_ecs_t *ecs, judd_entity_t *entity){
    return ecs->entities_names[entity - ecs->entities];
}
judd_entity_t *judd_get_entity_from_ecs(judd_ecs_t *ecs, char *name){
    int i;
    judd_entity_t *entity;
    for(i = 0; i < ecs->n_entities; i++)
        if(strcmp(ecs->entities_names[i], name) == 0)
            entity = ecs->entities+i;
    return entity;
}
char *judd_get_component_from_entity(judd_ecs_t *ecs, char *entity_name, char *pool_name){
    int i;
    judd_component_pool_t *pool = 0;
    judd_entity_t *entity;
    for(i = 0; i < ecs->n_entities; i++)
        if(strcmp(ecs->entities_names[i], entity_name) == 0)
            entity = ecs->entities+i;
    for(i = 0; i < ecs->n_components; i++)
        if(strcmp(ecs->pools_names[i], pool_name) == 0)
            pool = ecs->pools+i;
    return (pool->pool+(entity-ecs->entities)*pool->size);
}
judd_entity_t *judd_update_ecs(judd_ecs_t *ecs){
    int i;
    int j;
    for(j = 0; j < ecs->n_systems; j++){
        for(i = 0; i < ecs->n_entities; i++){
            if(!ecs->entities[i].sleeping && (ecs->systems[j]->match.components & ecs->entities[i].components) == ecs->systems[j]->match.components){
                ecs->systems[j]->fn(ecs, &(ecs->entities[i]));
            }
        }
    }
}
judd_entity_t *judd_remove_component_from_entity(judd_ecs_t *ecs, judd_entity_t *entity, char *name){
    int i;
    judd_component_pool_t *pool;
    for(i = 0; i < ecs->n_entities; i++)
        if(strcmp(ecs->pools_names[i], name) == 0)
            pool = ecs->pools+i;
    entity->components = ~(1 << (pool - ecs->pools)) & entity->components;
}
void judd_remove_component_pool_from_ecs(judd_ecs_t *ecs, char *name){
    int i;
    judd_component_pool_t *pool;
    for(i = 0; i < ecs->n_components; i++)
        if(strcmp(ecs->pools_names[i], name) == 0)
            pool = ecs->pools+i;

    free(ecs->pools_names[i]);
    free(ecs->pools[i].pool);
    memcpy(pool, pool+1, sizeof(judd_component_pool_t) * (ecs->n_components-i));
    memcpy(&(ecs->pools_names[i]), &(ecs->pools_names[i])+1, sizeof(char *) * (ecs->n_components-i));
}
void judd_remove_entity(judd_ecs_t *ecs, char *name){
    int i;
    judd_entity_t *entity;
    for(i = 0; i < ecs->n_entities; i++)
        if(strcmp(ecs->entities_names[i], name) == 0)
            entity = ecs->entities+i;

    free(ecs->entities_names[i]);
    memcpy(entity,  ecs->entities+1, sizeof(judd_component_pool_t) * (ecs->n_entities-i));
    memcpy(&(ecs->entities_names[i]), &(ecs->entities_names[i])+1, sizeof(char *) * (ecs->n_entities-i));
}
void judd_destroy_ecs(judd_ecs_t *ecs){
    int i;
    for(i = 0; i < ecs->max_entities; i++){
        judd_remove_entity(ecs, ecs->entities_names[i]);
    }
    free(ecs->entities);
    free(ecs->entities_names);
    for(i = 0; i < ecs->max_components; i++){
        judd_remove_component_pool_from_ecs(ecs, ecs->pools_names[i]);
    }
    free(ecs->pools);
    free(ecs->pools_names);
    for(i = 0; i < ecs->max_systems; i++){
        free(ecs->systems[i]);
    }
    free(ecs->systems);
    free(ecs);

    free(ecs);
}
#undef JUDD_ECS_IMPL
#endif
