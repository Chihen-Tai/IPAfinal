#include "veget.h"
#include <stdio.h>
/*
    [Veget function]
*/
Elements *New_Veget(int label)
{
     Veget *pDerivedObj = (Veget *)malloc(sizeof(Veget));
     Elements *pObj = New_Elements(label);
     // setting derived object member
     pDerivedObj->img = al_load_bitmap("assets/image/vege.png");
     pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
     pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
     _Veget_load_map(pDerivedObj);
     pDerivedObj->x = 0;
     pDerivedObj->y = 0;
     // setting the interact object
     pObj->inter_obj[pObj->inter_len++] = Character_L;
     // setting derived object function
     pObj->pDerivedObj = pDerivedObj;
     pObj->Draw = Veget_draw;
     pObj->Update = Veget_update;
     pObj->Interact = Veget_interact;
     pObj->Destroy = Veget_destory;
     return pObj;
}
void _Veget_load_map(Veget *Veget)
{
     FILE *data;
     data = fopen("assets/map/gamescene_map.txt", "r");
     for (int i = 0; i < 10; i++)
     {
          for (int j = 0; j < 16; j++)
          {
                fscanf(data, "%d", &Veget->map_data[i][j]);
          }
     }
     fclose(data);
}
void Veget_update(Elements *ele) {}
void Veget_interact(Elements *self, Elements *tar)
{
     if (tar->label == Character_L)
     {
          Character *chara = (Character *)(tar->pDerivedObj);
          int right_limit = WIDTH - chara->width / 2;
          int left_limit = 0 - chara->width / 2;
          if (chara->x < left_limit)
          {
                _Character_update_position(tar, (left_limit - chara->x), 0, chara->scene);
          }
          else if (chara->x > right_limit)
          {
                _Character_update_position(tar, (right_limit - chara->x), 0, chara->scene);
          }
     }
}
void Veget_draw(Elements *self)
{
     Veget *Obj = ((Veget *)(self->pDerivedObj));
     for (int i = 0; i < 10; i++)
     {
          for (int j = 0; j < 16; j++)
          {
                if (Obj->map_data[i][j]==11)
                {
                     al_draw_bitmap(Obj->img, Obj->x + j * Obj->width, Obj->y + i * Obj->height, 0);
                }
          }
     }
}
void Veget_destory(Elements *self)
{
     Veget *Obj = ((Veget *)(self->pDerivedObj));
     al_destroy_bitmap(Obj->img);
     free(Obj);
     free(self);
}
