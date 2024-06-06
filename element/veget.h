#ifndef VEGET_H_INCLUDED
#define VEGET_H_INCLUDED
#include "element.h"
#include "charater.h"
#include "../scene/gamescene.h" // for element label
/*
    [veget object]
*/
typedef struct _Veget
{
     int x, y;          // the position of image
     int width, height; // the width and height of image
     ALLEGRO_BITMAP *img;
     int map_data[10][16];
} Veget;

Elements *New_Veget(int label);
void _Veget_load_map(Veget *veget);
void Veget_update(Elements *self);
void Veget_interact(Elements *self, Elements *tar);
void Veget_draw(Elements *self);
void Veget_destory(Elements *self);

#endif
