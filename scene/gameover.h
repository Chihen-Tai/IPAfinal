#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "scene.h"
#include "../element/projectile.h"

typedef struct {
    ALLEGRO_FONT *font;
    ALLEGRO_BITMAP *background_image;
    ALLEGRO_FONT *fonten;
    ALLEGRO_FONT *fonts;
    ALLEGRO_SAMPLE *song;
} GameOver;

Scene *New_GameOver(int label, int displayScore);
void GameOver_update(Scene *self);
void GameOver_draw(Scene *self);
void GameOver_destroy(Scene *self);

#endif // GAMEOVER_H
