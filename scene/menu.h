#ifndef MENU_H
#define MENU_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_ttf.h>
#include "scene.h"

extern int window;
typedef struct Menu {
    ALLEGRO_FONT *font;
    ALLEGRO_FONT *font_title;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE *select;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    ALLEGRO_SAMPLE_INSTANCE *sample_select_instance;
    ALLEGRO_BITMAP *background_image;
    int title_x;
    int title_y;
    int selected_option;
    int playing;
    int mplaying;
    double last_key_time; // 添加一个字段来跟踪上次按键处理的时间 
} Menu;

Scene *New_Menu(int label);
void menu_update(Scene *self);
void menu_draw(Scene *self);
void menu_destroy(Scene *self);

#endif
