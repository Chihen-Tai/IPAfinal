#ifndef PAN_H_INCLUDED
#define PAN_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
    [pan object]
*/
typedef struct _Pan
{
     int x, y;          // the position of image
     int width, height; // the width and height of image
     ALLEGRO_BITMAP *img;
     Shape *hitbox; // the hitbox of object
} Pan;
Elements *New_Pan(int label);
void Pan_update(Elements *self);
void Pan_interact(Elements *self, Elements *tar);
void Pan_draw(Elements *self);
void Pan_destory(Elements *self);

#endif
