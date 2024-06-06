#include "gameover.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include "gamescene.h"

Scene *New_GameOver(int label, int displayScore)
{
    GameOver *pDerivedObj = (GameOver *)malloc(sizeof(GameOver));
    Scene *pObj = (Scene *)malloc(sizeof(Scene));

    pDerivedObj->font = al_load_font("assets/font/chinese.ttf", 60, 0);
    pDerivedObj->fonts = al_load_font("assets/font/chinese.ttf", 30, 0);
    pDerivedObj->fonten =al_load_font("assets/font/C.TTF", 100, 0);
    pDerivedObj->song = al_load_sample("assets/sound/gameover.mp3");
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = GameOver_update;
    pObj->Draw = GameOver_draw;
    pObj->Destroy = GameOver_destroy;
    pObj->scene_end = false;
    pObj->score = displayScore;
    al_play_sample(pDerivedObj->song, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);

    return pObj;
}

void GameOver_draw(Scene *self)
{
    GameOver *Obj = (GameOver *)(self->pDerivedObj);
    al_clear_to_color(al_map_rgb(0, 0, 0));

    // Draw score
    char score_text[50];
    
    sprintf(score_text, "Score: %d", self->score);
    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), 100, 100, ALLEGRO_ALIGN_LEFT, score_text);
    al_draw_text(Obj->fonten, al_map_rgb(255,255,255), WIDTH / 2, HEIGHT / 2 , ALLEGRO_ALIGN_CENTRE, "TIMES UP!!!");
    al_draw_text(Obj->fonts, al_map_rgb(255,255,255), WIDTH / 2, HEIGHT / 2 +100, ALLEGRO_ALIGN_CENTRE, "ESC go back to menu");
    
}

void GameOver_destroy(Scene *self)
{
    GameOver *Obj = (GameOver *)(self->pDerivedObj);
    ALLEGRO_SAMPLE *song = Obj->song;
    if (Obj)
    {
        if (Obj->font)
        {
            al_destroy_font(Obj->font);
        }
    }
    free(self);
    al_destroy_sample(song);
}

void GameOver_update(Scene *self)
{
    if (key_state[ALLEGRO_KEY_ESCAPE])
    {
        self->scene_end = true;
        window = 0;
        return;
    }
}
