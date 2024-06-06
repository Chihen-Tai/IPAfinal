#include "introscene.h"
#include "../scene/sceneManager.h"
#include <allegro5/allegro_audio.h>
#include "../algif5/src/algif.h"
#include <stdio.h>
#include <stdlib.h>

Scene *New_Introduction(int label)
{
    Introduction *pDerivedObj = (Introduction *)malloc(sizeof(Introduction));

    Scene *pObj = (Scene *)malloc(sizeof(Scene));

    pDerivedObj->font = al_load_font("assets/font/chinese.ttf", 30, 0);
    pDerivedObj->song = al_load_sample("assets/sound/intro.mp3");

    pDerivedObj->background_image = al_load_bitmap("assets/image/stage.jpg");
    al_play_sample(pDerivedObj->song, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);

    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = (fptrUpdate)Introduction_update;
    pObj->Draw = (fptrDraw)Introduction_draw;
    pObj->Destroy = (fptrDestroy)Introduction_destroy;
    pObj->scene_end = false;

    return pObj;
}

void Introduction_update(Scene *self)
{
    if (key_state[ALLEGRO_KEY_ESCAPE])
    {
        self->scene_end = true;
        window = 0;
        return;
    }
}

void Introduction_draw(Scene *self)
{
    Introduction *Obj = (Introduction *)(self->pDerivedObj);
    al_clear_to_color(al_map_rgb(0, 0, 0));

    if (Obj->background_image)
    {
        al_draw_bitmap(Obj->background_image, 0, 0, 0);
    }
    al_draw_text(Obj->font, al_map_rgb(0,0,0), WIDTH / 2, HEIGHT / 2-140, ALLEGRO_ALIGN_CENTRE, "遊戲簡介");
    al_draw_text(Obj->font, al_map_rgb(0,0,0), WIDTH / 2, HEIGHT / 2-100, ALLEGRO_ALIGN_CENTRE, "今天媽媽不再加家裡沒人做飯你必須擔起這個重任");
    al_draw_text(Obj->font, al_map_rgb(0,0,0), WIDTH / 2, HEIGHT / 2-60, ALLEGRO_ALIGN_CENTRE, "遊戲規則");
    al_draw_text(Obj->font, al_map_rgb(0,0,0), WIDTH / 2, HEIGHT / 2-20, ALLEGRO_ALIGN_CENTRE, "時間結束之錢拿到盡量高的分數");
    al_draw_text(Obj->font, al_map_rgb(0,0,0), WIDTH / 2, HEIGHT / 2 + 20, ALLEGRO_ALIGN_CENTRE, "WASD移動角色");
    al_draw_text(Obj->font, al_map_rgb(0,0,0), WIDTH / 2, HEIGHT / 2 + 60, ALLEGRO_ALIGN_CENTRE, "W(上)S(下)A(左)D(右)");
    al_draw_text(Obj->font, al_map_rgb(0,0,0), WIDTH / 2, HEIGHT / 2 + 100, ALLEGRO_ALIGN_CENTRE, "ESC返回上一頁");
}

void Introduction_destroy(Scene *self)
{
    Introduction *Obj = (Introduction *)(self->pDerivedObj);
    ALLEGRO_SAMPLE *song = Obj->song;
    if (Obj)
    {
        if (Obj->font)
        {
            al_destroy_font(Obj->font);
        }
        if (Obj->background_image)
        {
            al_destroy_bitmap(Obj->background_image);
        }
        free(Obj);
    }
    free(self);
    al_destroy_sample(song);
}
