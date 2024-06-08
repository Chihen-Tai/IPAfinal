#include "pan.h"
#include "../shapes/Rectangle.h"
/*
    [pan function]
*/
Elements *New_Pan(int label)
{
     Pan *pDerivedObj = (Pan *)malloc(sizeof(Pan));
     Elements *pObj = New_Elements(label);
     // setting derived object member
     pDerivedObj->img = al_load_bitmap("assets/image/pan.png");
     pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
     pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
     pDerivedObj->x = 530;
     pDerivedObj->y = 325;
     pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x + pDerivedObj->width / 3,
                                                     pDerivedObj->y + pDerivedObj->height / 3,
                                                     pDerivedObj->x + 2 * pDerivedObj->width / 3,
                                                     pDerivedObj->y + 2 * pDerivedObj->height / 3);
     // setting derived object function
     pObj->pDerivedObj = pDerivedObj;
     pObj->Update = Pan_update;
     pObj->Interact = Pan_interact;
     pObj->Draw = Pan_draw;
     pObj->Destroy = Pan_destory;
     return pObj;
}
void Pan_update(Elements *self) {}
void Pan_interact(Elements *self, Elements *tar) {}
void Pan_draw(Elements *self)
{
     Pan *Obj = ((Pan *)(self->pDerivedObj));
     al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Pan_destory(Elements *self)
{
     Pan *Obj = ((Pan *)(self->pDerivedObj));
     al_destroy_bitmap(Obj->img);
     free(Obj->hitbox);
     free(Obj);
     free(self);
}
