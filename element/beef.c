#include "Beef.h"
#include <stdio.h>
/*
   [Beef function]
*/
Elements *New_Beef(int label) {
    Beef *pDerivedObj = (Beef *)malloc(sizeof(Beef));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/Beef.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    _Beef_load_map(pDerivedObj);
    pDerivedObj->x = 0;         // 中心x
    pDerivedObj->y = 0;         // 中心y
    pDerivedObj->is_picked = 0; // 沒拿起來
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Character_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Draw = Beef_draw;
    pObj->Update = Beef_update;
    pObj->Interact = Beef_interact;
    pObj->Destroy = Beef_destory;
    return pObj;
}

void _Beef_load_map(Beef *Beef) {
    FILE *data;
    data = fopen("assets/map/gamescene_map.txt", "r");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 16; j++) {
            fscanf(data, "%d", &Beef->map_data[i][j]);
        }
    }
    fclose(data);
}
const ALLEGRO_KEYBOARD_STATE *keyboard_state; // 設定
void Beef_update(Elements *ele) {
    Beef *Obj = (Beef *)(ele->pDerivedObj);
    if (key_state[ALLEGRO_KEY_Z]) { // 偵測拿起來
        Obj->is_picked = false;
    }
}
void Beef_interact(Elements *self, Elements *tar) {
    if (tar->label == Character_L) {
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

// TEST

void Beef_draw(Elements *self) {
    Beef *Obj = ((Beef *)(self->pDerivedObj));
    if (Obj->is_picked)
        al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
    else {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 16; j++) {
                if (Obj->map_data[i][j] == 10) { // 跟著動
                    al_draw_bitmap(Obj->img, Obj->x + j * Obj->width, Obj->y + i * Obj->height, 0);
                }
            }
        }
    }
}
void Beef_destory(Elements *self) {
    Beef *Obj = ((Beef *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj);
    free(self);
}
