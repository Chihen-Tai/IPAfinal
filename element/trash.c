#include "trash.h"
#include <stdio.h>
/*
    [Trash function]
*/
Elements *New_Trash(int label)
{
     Trash *pDerivedObj = (Trash *)malloc(sizeof(Trash));
     Elements *pObj = New_Elements(label);
     // setting derived object member
     pDerivedObj->img = al_load_bitmap("assets/image/trash.png");
     pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
     pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
     _Trash_load_map(pDerivedObj);
     pDerivedObj->x = 0;
     pDerivedObj->y = 0;
     // setting the interact object
     pObj->inter_obj[pObj->inter_len++] = Character_L;
     // setting derived object function
     pObj->pDerivedObj = pDerivedObj;
     pObj->Draw = Trash_draw;
     pObj->Update = Trash_update;
     pObj->Interact = Trash_interact;
     pObj->Destroy = Trash_destory;
     return pObj;
}
void _Trash_load_map(Trash *Trash)
{
     FILE *data;
     data = fopen("assets/map/gamescene_map.txt", "r");
     for (int i = 0; i < 10; i++)
     {
          for (int j = 0; j < 16; j++)
          {
                fscanf(data, "%d", &Trash->map_data[i][j]);
          }
     }
     fclose(data);
}
void Trash_update(Elements *ele) {}
void Trash_interact(Elements *self, Elements *tar)
{
     if (tar->label == Character_L)
     {
          Character *chara = (Character *)(tar->pDerivedObj);
          int right_limit = WIDTH - chara->width / 2;
          int left_limit = 0 - chara->width / 2;
          if (chara->x < left_limit)
          {
                _Character_update_position(tar, (left_limit - chara->x), 0);
          }
          else if (chara->x > right_limit)
          {
                _Character_update_position(tar, (right_limit - chara->x), 0);
          }
     }
}
void Trash_draw(Elements *self)
{
     Trash *Obj = ((Trash *)(self->pDerivedObj));
     for (int i = 0; i < 10; i++)
     {
          for (int j = 0; j < 16; j++)
          {
                if (Obj->map_data[i][j]==2)
                {
                     al_draw_bitmap(Obj->img, Obj->x + j * Obj->width, Obj->y + i * Obj->height, 0);
                }
          }
     }
}
void Trash_destory(Elements *self)
{
     Trash *Obj = ((Trash *)(self->pDerivedObj));
     al_destroy_bitmap(Obj->img);
     free(Obj);
     free(self);
}
