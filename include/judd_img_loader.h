#ifndef JUDD_IMG_LOADER_H
#define JUDD_IMG_LOADER_H
#include <stdio.h>

char *judd_load_bmp(char *path);

#endif
#ifdef JUDD_IMG_LOADER_IMPL
#undef JUDD_IMG_LOADER_IMPL
char *judd_load_bmp(char *path){
    FILE *file = fopen(path, "r");
    char  *data;
    int start[2];
    uint32_t size;
    uint32_t offset;
    uint32_t headersize;
    uint32_t comp;
    int8_t w;
    int8_t h;
    uint16_t planes;
    uint16_t bitspixel;
    if(!file){
        perror("Error");
        printf("Invalid file name: %s\n", path);
        return NULL;
    }
    if(((start[0] = fgetc(file)) != 'B') || fgetc(file) != 'M'){
        printf("Invalid BMP file starting with %d\n", start[0]);
    }
    size = fgetc(file);
    size += fgetc(file) << 8;
    size += fgetc(file) << 16;
    size += fgetc(file) << 24;
    fgetc(file);fgetc(file);fgetc(file);fgetc(file);
    offset = fgetc(file);
    offset += fgetc(file) << 8;
    offset += fgetc(file) << 16;
    offset += fgetc(file) << 24;
    headersize = fgetc(file);
    headersize += fgetc(file) << 8;
    headersize += fgetc(file) << 16;
    headersize += fgetc(file) << 24;
    w = fgetc(file);
    w += fgetc(file) << 8;
    w += fgetc(file) << 16;
    w += fgetc(file) << 24;
    h = fgetc(file);
    h += fgetc(file) << 8;
    h += fgetc(file) << 16;
    h += fgetc(file) << 24;
    planes = fgetc(file);
    planes += fgetc(file) << 8;
    bitspixel = fgetc(file);
    bitspixel += fgetc(file) << 8;
    comp = fgetc(file);
    comp += fgetc(file) >> 8;
    comp += fgetc(file) >> 16;
    comp += fgetc(file) >> 24;
    if(comp){
        printf("Unsupported bitmap format\n");
    }
    fgetc(file);fgetc(file);fgetc(file);fgetc(file);
    fgetc(file);fgetc(file);fgetc(file);fgetc(file);
    fgetc(file);fgetc(file);fgetc(file);fgetc(file);
    fgetc(file);fgetc(file);fgetc(file);fgetc(file);
    fgetc(file);//fgetc(file);fgetc(file);fgetc(file);
    data = malloc(w * h * bitspixel / 8 * sizeof(char));
    fread(data, w * h * bitspixel / 8, 1, file);
    return data;
}
#endif
