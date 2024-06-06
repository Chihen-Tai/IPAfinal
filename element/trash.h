#ifndef TRASH_H_INCLUDED
#define TRASH_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
    [trash object]
*/
typedef struct _Trash
{
     int x, y;          // the position of image
     int width, height; // the width and height of image
     ALLEGRO_BITMAP *img;
     Shape *hitbox; // the hitbox of object
} Trash;
Elements *New_Trash(int label);
void Trash_update(Elements *self);
void Trash_interact(Elements *self, Elements *tar);
void Trash_draw(Elements *self);
void Trash_destory(Elements *self);

#endif
