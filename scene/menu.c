#include "menu.h"
#include "../scene/sceneManager.h"
#include <stdio.h>
#include <stdlib.h>

Scene *New_Menu(int label) {
    Menu *pDerivedObj = (Menu *)malloc(sizeof(Menu));
    Scene *pObj = (Scene *)malloc(sizeof(Scene));

    pDerivedObj->font = al_load_ttf_font("assets/font/main.ttf", 30, 0);
    pDerivedObj->font_title = al_load_ttf_font("assets/font/main.ttf", 60, 0);
    pDerivedObj->song = al_load_sample("assets/sound/relaxing.mp3");
    al_reserve_samples(20);
    pDerivedObj->select = al_load_sample("assets/sound/select.mp3");
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    pDerivedObj->sample_select_instance = al_create_sample_instance(pDerivedObj->select);
    pDerivedObj->title_x = WIDTH / 2;
    pDerivedObj->title_y = HEIGHT / 2;
    pDerivedObj->selected_option = 0;
    pDerivedObj->last_key_time = 0.0;
    pDerivedObj->background_image = al_load_bitmap("assets/image/login.jpg");

    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.1);

    al_attach_sample_instance_to_mixer(pDerivedObj->sample_select_instance, al_get_default_mixer());
    al_set_sample_instance_gain(pDerivedObj->sample_select_instance, 1.0);


    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = menu_update;
    pObj->Draw = menu_draw;
    pObj->Destroy = menu_destroy;
    pObj->scene_end = false;

    al_play_sample_instance(pDerivedObj->sample_instance);

    return pObj;
}

void menu_update(Scene *self) {
    Menu *Obj = (Menu *)(self->pDerivedObj);
    if (key_state[ALLEGRO_KEY_ENTER]) {
        al_play_sample_instance(Obj->sample_select_instance);
        switch (Obj->selected_option) {
            case 0:
                self->scene_end = true;
                window = 1;
                break;
            case 1:
                self->scene_end = true;
                window = 2;
                break;
            case 2:
                self->scene_end = true;
                window = -1;
                break;
        }
    }

    const double KEY_PRESS_INTERVAL = 0.2;

    if (al_get_time() - Obj->last_key_time > KEY_PRESS_INTERVAL) {
        if (key_state[ALLEGRO_KEY_W] || key_state[ALLEGRO_KEY_UP]) {
            Obj->selected_option--;
            if (Obj->selected_option < 0)
                Obj->selected_option = 2;
            Obj->last_key_time = al_get_time();
            
            // 播放选择音效
            al_play_sample_instance(Obj->sample_select_instance);

        } else if (key_state[ALLEGRO_KEY_S] || key_state[ALLEGRO_KEY_DOWN]) {
            Obj->selected_option++;
            if (Obj->selected_option > 2)
                Obj->selected_option = 0;
            Obj->last_key_time = al_get_time();

            // 播放选择音效
            al_play_sample_instance(Obj->sample_select_instance);
        }
    }
}


void menu_draw(Scene *self) {
    Menu *Obj = (Menu *)(self->pDerivedObj);
    al_clear_to_color(al_map_rgb(0, 0, 0));

    if (Obj->background_image) {
        al_draw_bitmap(Obj->background_image, 0, 0, 0);
    }

    al_draw_text(Obj->font_title, al_map_rgb(255, 0, 0), WIDTH / 2, HEIGHT / 4, ALLEGRO_ALIGN_CENTRE, "kitchen chaos");

    const char *options[] = {"Start Game", "Introduction", "Exit"};
    for (int i = 0; i < 3; i++) {
        ALLEGRO_COLOR color = (i == Obj->selected_option) ? al_map_rgb(0, 0, 0) : al_map_rgb(255, 255, 255);
        al_draw_text(Obj->font, color, Obj->title_x, Obj->title_y + i * 40, ALLEGRO_ALIGN_CENTRE, options[i]);
    }
}

void menu_destroy(Scene *self) {
    Menu *Obj = (Menu *)(self->pDerivedObj);
    if (Obj->font) al_destroy_font(Obj->font);
    if (Obj->font_title) al_destroy_font(Obj->font_title);
    if (Obj->song) al_destroy_sample(Obj->song);
    if (Obj->sample_instance) al_destroy_sample_instance(Obj->sample_instance);
    if (Obj->select) al_destroy_sample(Obj->select);
    if (Obj->sample_select_instance) al_destroy_sample_instance(Obj->sample_select_instance);
    if (Obj->background_image) al_destroy_bitmap(Obj->background_image);
    free(Obj);
    free(self);
}
