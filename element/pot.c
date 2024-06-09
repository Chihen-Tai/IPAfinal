#include "pot.h"
#include "../shapes/Rectangle.h"
/*
    [pot function]
*/
Elements *New_pot(int label)
{
     pot *pDerivedObj = (pot *)malloc(sizeof(pot));
     Elements *pObj = New_Elements(label);
     // setting derived object member
     pDerivedObj->img = al_load_bitmap("assets/image/pot.png");
     pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
     pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
     pDerivedObj->x = 430;
     pDerivedObj->y = 40;
     pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x + pDerivedObj->width / 3,
                                                     pDerivedObj->y + pDerivedObj->height / 3,
                                                     pDerivedObj->x + 2 * pDerivedObj->width / 3,
                                                     pDerivedObj->y + 2 * pDerivedObj->height / 3);
     // setting derived object function
     pObj->pDerivedObj = pDerivedObj;
     pObj->Update = pot_update;
     pObj->Interact = pot_interact;
     pObj->Draw = pot_draw;
     pObj->Destroy = pot_destory;
     return pObj;
}
void pot_update(Elements *self) {}
void pot_interact(Elements *self, Elements *tar) {}
void pot_draw(Elements *self)
{
     pot *Obj = ((pot *)(self->pDerivedObj));
     al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void pot_destory(Elements *self)
{
     pot *Obj = ((pot *)(self->pDerivedObj));
     al_destroy_bitmap(Obj->img);
     free(Obj->hitbox);
     free(Obj);
     free(self);
}
