#ifndef FOOD_H_INCLUDED
#define FOOD_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
    [food object]
*/
typedef struct _Food
{
     int x, y;          // the position of image
     int width, height; // the width and height of image
     ALLEGRO_BITMAP *img;
     Shape *hitbox; // the hitbox of object
} Food;
Elements *New_Food(int label);
void Food_update(Elements *self);
void Food_interact(Elements *self, Elements *tar);
void Food_draw(Elements *self);
void Food_destory(Elements *self);

#endif