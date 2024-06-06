#ifndef BEEF_H_INCLUDED
#define BEEF_H_INCLUDED
#include "element.h"
#include "charater.h"
#include "../scene/gamescene.h" // for element label
/*
    [beef object]
*/
typedef struct _Beef
{
     int x, y;          // the position of image
     int width, height; // the width and height of image
     ALLEGRO_BITMAP *img;
     int map_data[10][16];
} Beef;

Elements *New_Beef(int label);
void _Beef_load_map(Beef *beef);
void Beef_update(Elements *self);
void Beef_interact(Elements *self, Elements *tar);
void Beef_draw(Elements *self);
void Beef_destory(Elements *self);

#endif
