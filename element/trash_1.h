#ifndef TRASH_1_H_INCLUDED
#define TRASH_1_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
    [trash_1 object]
*/
typedef struct _Trash_1
{
     int x, y;          // the position of image
     int width, height; // the width and height of image
     ALLEGRO_BITMAP *img;
     Shape *hitbox; // the hitbox of object
} Trash_1;
Elements *New_Trash_1(int label);
void Trash_1_update(Elements *self);
void Trash_1_interact(Elements *self, Elements *tar);
void Trash_1_draw(Elements *self);
void Trash_1_destory(Elements *self);

#endif
