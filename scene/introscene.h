#ifndef INTROSCENE_H
#define INTROSCENE_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "scene.h"
#include "../element/projectile.h"

typedef struct {
    ALLEGRO_FONT *font;
    ALLEGRO_BITMAP *background_image;
    ALLEGRO_SAMPLE *song;
} Introduction;

Scene *New_Introduction(int label);
void Introduction_update(Scene *self);
void Introduction_draw(Scene *self);
void Introduction_destroy(Scene *self);

#endif // INTROSCENE_H
