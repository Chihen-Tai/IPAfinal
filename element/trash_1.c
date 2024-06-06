#include "trash_1.h"
#include "../shapes/Rectangle.h"
/*
    [trash function]
*/
Elements *New_Trash_1(int label)
{
     Trash_1 *pDerivedObj = (Trash_1 *)malloc(sizeof(Trash_1));
     Elements *pObj = New_Elements(label);
     // setting derived object member
     pDerivedObj->img = al_load_bitmap("assets/image/trash.png");
     pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
     pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
     pDerivedObj->x = 1075;
     pDerivedObj->y = 560;
     pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x + pDerivedObj->width / 3,
                                                     pDerivedObj->y + pDerivedObj->height / 3,
                                                     pDerivedObj->x + 2 * pDerivedObj->width / 3,
                                                     pDerivedObj->y + 2 * pDerivedObj->height / 3);
     // setting derived object function
     pObj->pDerivedObj = pDerivedObj;
     pObj->Update = Trash_1_update;
     pObj->Interact = Trash_1_interact;
     pObj->Draw = Trash_1_draw;
     pObj->Destroy = Trash_1_destory;
     return pObj;
}
void Trash_1_update(Elements *self) {}
void Trash_1_interact(Elements *self, Elements *tar) {}
void Trash_1_draw(Elements *self)
{
     Trash_1 *Obj = ((Trash_1 *)(self->pDerivedObj));
     al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Trash_1_destory(Elements *self)
{
     Trash_1 *Obj = ((Trash_1 *)(self->pDerivedObj));
     al_destroy_bitmap(Obj->img);
     free(Obj->hitbox);
     free(Obj);
     free(self);
}
