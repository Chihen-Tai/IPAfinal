#include "charater.h"
#include "../algif5/src/algif.h"
#include "../scene/sceneManager.h"
#include "../shapes/Rectangle.h"
#include "projectile.h"
#include <stdio.h>
/*
   [Character function]
*/

Elements *New_Character(int label) {
    Character *pDerivedObj = (Character *)malloc(sizeof(Character));
    Elements *pObj = New_Elements(label);
    // setting derived object member

    // load character images
    char state_string[3][10] = {"stop", "move", "attack"};

    // 應該改成 停 走 拿(米 肉 蝦 菜) 用(平底鍋 鍋 垃圾桶) 這幾個狀態
    for (int i = 0; i < 3; i++) {
        char buffer[50];
        sprintf(buffer, "assets/image/chara_%s.gif", state_string[i]);
        pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    }

    // load effective sound
    ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/godhotpot.mp3");
    // 統神pot 要留嗎

    pDerivedObj->atk_Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pDerivedObj->atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->atk_Sound, al_get_default_mixer());

    // initial the geometric information of character
    pDerivedObj->width = pDerivedObj->gif_status[0]->width;
    pDerivedObj->height = pDerivedObj->gif_status[0]->height;
    pDerivedObj->x = 300;
    pDerivedObj->y = HEIGHT - pDerivedObj->height - 60;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x, pDerivedObj->y, pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);
    pDerivedObj->dir = false;
    // true: face to right, false: face to left

    // 我們左右有處理嗎 忘記惹

    //  initial the animation component
    pDerivedObj->state = STOP;
    pDerivedObj->new_proj = false;
    pObj->pDerivedObj = pDerivedObj;

    // setting derived object function
    pObj->Draw = Character_draw;
    pObj->Update = Character_update;
    pObj->Interact = Character_interact;
    pObj->Destroy = Character_destory;
    return pObj;
}
void Character_update(Elements *const ele) {

    // use the idea of finite state machine to deal with different state
    Character *chara = ((Character *)(ele->pDerivedObj));
    if (chara->state == STOP) {
        if (key_state[ALLEGRO_KEY_SPACE]) {
            chara->state = ATK;
        } else if (key_state[ALLEGRO_KEY_A] && key_state[ALLEGRO_KEY_W]) {
            chara->dir = false;
            _Character_update_position(ele, -5, -5);
            chara->state = MOVE;
        } else if (key_state[ALLEGRO_KEY_A] && key_state[ALLEGRO_KEY_S]) {
            chara->dir = false;
            _Character_update_position(ele, -5, 5);
            chara->state = MOVE;
        } else if (key_state[ALLEGRO_KEY_D] && key_state[ALLEGRO_KEY_W]) {
            chara->dir = true;
            _Character_update_position(ele, 5, -5);
            chara->state = MOVE;
        } else if (key_state[ALLEGRO_KEY_D] && key_state[ALLEGRO_KEY_S]) {
            chara->dir = true;
            _Character_update_position(ele, 5, 5);
            chara->state = MOVE;
        } else if (key_state[ALLEGRO_KEY_A]) {
            chara->dir = false;
            _Character_update_position(ele, -5, 0);
            chara->state = MOVE;
        } else if (key_state[ALLEGRO_KEY_D]) {
            chara->dir = true;
            _Character_update_position(ele, 5, 0);
            chara->state = MOVE;
        } else if (key_state[ALLEGRO_KEY_W]) {
            _Character_update_position(ele, 0, -5);
            chara->state = MOVE;
        } else if (key_state[ALLEGRO_KEY_S]) {
            _Character_update_position(ele, 0, 5);
            chara->state = MOVE;
        }

        else {
            chara->state = STOP;
        }
    } else if (chara->state == MOVE) {
        if (key_state[ALLEGRO_KEY_SPACE]) {
            chara->state = ATK;
        } else if (key_state[ALLEGRO_KEY_A] && key_state[ALLEGRO_KEY_W]) {
            chara->dir = false;
            _Character_update_position(ele, -5, -5);
            chara->state = MOVE;
        } else if (key_state[ALLEGRO_KEY_A] && key_state[ALLEGRO_KEY_S]) {
            chara->dir = false;
            _Character_update_position(ele, -5, 5);
            chara->state = MOVE;
        } else if (key_state[ALLEGRO_KEY_D] && key_state[ALLEGRO_KEY_W]) {
            chara->dir = true;
            _Character_update_position(ele, 5, -5);
            chara->state = MOVE;
        } else if (key_state[ALLEGRO_KEY_D] && key_state[ALLEGRO_KEY_S]) {
            chara->dir = true;
            _Character_update_position(ele, 5, 5);
            chara->state = MOVE;
        } else if (key_state[ALLEGRO_KEY_A]) {
            chara->dir = false;
            _Character_update_position(ele, -5, 0);
            chara->state = MOVE;
        } else if (key_state[ALLEGRO_KEY_D]) {
            chara->dir = true;
            _Character_update_position(ele, 5, 0);
            chara->state = MOVE;
        } else if (key_state[ALLEGRO_KEY_W]) {
            _Character_update_position(ele, 0, -5);
            chara->state = MOVE;
        } else if (key_state[ALLEGRO_KEY_S]) {
            _Character_update_position(ele, 0, 5);
            chara->state = MOVE;
        }
        if (chara->gif_status[chara->state]->done)
            chara->state = STOP;
    } else if (chara->state == ATK) {
        if (chara->gif_status[chara->state]->done) {
            chara->state = STOP;
            chara->new_proj = false;
        }
        if (chara->gif_status[ATK]->display_index == 2 && chara->new_proj == false) {
            Elements *pro;
            if (chara->dir) {
                pro = New_Projectile(Projectile_L, chara->x + chara->width - 100, chara->y + 10, 5);
            } else {
                pro = New_Projectile(Projectile_L, chara->x - 50, chara->y + 10, -5);
            }
            _Register_elements(scene, pro);
            chara->new_proj = true;
        }
    }
}

void Character_draw(Elements *const ele) {
    Character *chara = ((Character *)(ele->pDerivedObj));
    ALLEGRO_BITMAP *frame = algif_get_bitmap(chara->gif_status[chara->state], al_get_time());

    if (frame) {
        al_draw_bitmap(frame, chara->x, chara->y, chara->dir ? ALLEGRO_FLIP_HORIZONTAL : 0);
    }

    if (chara->state == ATK && chara->gif_status[ATK]->display_index == 2) {
        al_play_sample_instance(chara->atk_Sound);
    }
}

void Character_destory(Elements *const ele) {
    Character *Obj = ((Character *)(ele->pDerivedObj));

    al_destroy_sample_instance(Obj->atk_Sound);
    for (int i = 0; i < 3; i++) {
        algif_destroy_animation(Obj->gif_status[i]);
    }

    free(Obj->hitbox);
    free(Obj);
    free(ele);
}

void _Character_update_position(Elements *const ele, int dx, int dy) {
    Character *chara = ((Character *)(ele->pDerivedObj));
    int new_x = chara->x + dx;
    int new_y = chara->y + dy;

    // Check if the new position is within the boundaries
    if (new_x >= 0 && new_x + chara->width <= WIDTH) {
        chara->x = new_x;
        chara->hitbox->update_center_x(chara->hitbox, dx);
    }

    if (new_y >= 0 && new_y + chara->height <= HEIGHT) {
        chara->y = new_y;
        chara->hitbox->update_center_y(chara->hitbox, dy);
    }
}

void Character_interact(Elements *const self, Elements *const target) {
}
