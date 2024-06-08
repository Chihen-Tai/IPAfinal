#ifndef POT_H_INCLUDED
#define POT_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
    [pot object]
*/
typedef struct _pot
{
     int x, y;          // the position of image
     int width, height; // the width and height of image
     ALLEGRO_BITMAP *img;
     Shape *hitbox; // the hitbox of object
} pot;
Elements *New_pot(int label);
void pot_update(Elements *self);
void pot_interact(Elements *self, Elements *tar);
void pot_draw(Elements *self);
void pot_destory(Elements *self);

#endif
