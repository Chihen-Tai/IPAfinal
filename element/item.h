#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include "element.h"
#include "../scene/gamescene.h"
#include "charater.h"

typedef struct {
    int x, y; 
    int width, height; 
    ALLEGRO_BITMAP *bitmap; 
} Item;

Elements *New_Item(int x, int y, const char *bitmap_path);
void Item_draw(Elements *const ele);
void Item_update(Elements *const ele);
void Item_interact(Elements *const self, Elements *const target);
void Item_destroy(Elements *const ele);

#endif
