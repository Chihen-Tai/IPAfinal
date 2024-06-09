#include "teleport.h"
#include <stdbool.h>
/*
   [teleport function]
*/
Elements *New_Teleport(int label)
{
    Teleport *pDerivedObj = (Teleport *)malloc(sizeof(Teleport));
    Elements *pObj = New_Elements(label);
    pDerivedObj->img = al_load_bitmap("assets/image/teleport.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = WIDTH - pDerivedObj->width - 150;
    pDerivedObj->y = 100;
    pDerivedObj->activate = false;
    pObj->inter_obj[pObj->inter_len++] = Character_L;
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Teleport_update;
    pObj->Interact = Teleport_interact;
    pObj->Draw = Teleport_draw;
    pObj->Destroy = Teleport_destory;
    return pObj;
}
void Teleport_update(Elements *self)
{
    Teleport *Obj = ((Teleport *)(self->pDerivedObj));
    if (key_state[ALLEGRO_KEY_W])
    {
        Obj->activate = true;
    }
    else
    {
        Obj->activate = false;
    }

    // 打印激活状态
    //printf("Teleport activate state: %d\n", Obj->activate);
}

void Teleport_interact(Elements *self, Elements *tar)
{
    if (tar->label == Character_L)
    {
        Character *chara = (Character *)(tar->pDerivedObj);
        Teleport *Obj = (Teleport *)(self->pDerivedObj);

        int margin = 5; // 设置一个检测范围的边界

        // 打印调试信息
        //printf("Character position: x=%d, y=%d\n", chara->x, chara->y);
        //printf("Teleport position: x=%d, y=%d, width=%d, height=%d, activate=%d\n", Obj->x, Obj->y, Obj->width, Obj->height, Obj->activate);

        if (chara->x + margin >= Obj->x &&
            chara->x <= Obj->x + Obj->width + margin &&
            chara->y >= Obj->y &&
            chara->y <= Obj->y + Obj->height &&
            Obj->activate)
        {
            _Character_update_position(tar, -500, -200, chara->scene);
            //printf("Teleport success\n");
        }
        else
        {
            //printf("Teleport condition not met\n");
        }
    }
}
void Teleport_draw(Elements *self)
{
    Teleport *Obj = ((Teleport *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Teleport_destory(Elements *self)
{
    Teleport *Obj = ((Teleport *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj);
    free(self);
}
