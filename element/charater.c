#include "charater.h"
#include "../algif5/src/algif.h"
#include "../scene/sceneManager.h"
#include "../shapes/Rectangle.h"
#include "floor.h"
#include "projectile.h"
#include <stdio.h>

Elements *New_Character(int label, Scene *scene) {
    Character *pDerivedObj = (Character *)malloc(sizeof(Character));
    Elements *pObj = New_Elements(label);
    char state_string[3][10] = {"stop", "move", "attack"};
    // 應該改成 停 走 拿(米 肉 蝦 菜) 用(平底鍋 鍋 垃圾桶) 這幾個狀態
    for (int i = 0; i < 3; i++) {
        char buffer[50];
        sprintf(buffer, "assets/image/chara_%s.gif", state_string[i]);
        pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
        if (!pDerivedObj->gif_status[i]) {
            fprintf(stderr, "Failed to load GIF: %s\n", buffer);
            // Properly free previously loaded resources
            for (int j = 0; j < i; j++)
                algif_destroy_animation(pDerivedObj->gif_status[j]);
            free(pDerivedObj);
            free(pObj);
            return NULL;
        }
    }
    ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/godhotpot.mp3");
    pDerivedObj->atk_Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pDerivedObj->atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->atk_Sound, al_get_default_mixer());
    pDerivedObj->width = pDerivedObj->gif_status[0]->width;
    pDerivedObj->height = pDerivedObj->gif_status[0]->height;
    pDerivedObj->x = 80;
    pDerivedObj->y = 80;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x, pDerivedObj->y, pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);
    if (!pDerivedObj->hitbox) {
        fprintf(stderr, "Failed to create hitbox\n");
        al_destroy_sample_instance(pDerivedObj->atk_Sound);
        for (int i = 0; i < 3; i++)
            algif_destroy_animation(pDerivedObj->gif_status[i]);
        free(pDerivedObj);
        free(pObj);
        return NULL;
    }
    pDerivedObj->dir = false;
    pDerivedObj->state = STOP;
    pDerivedObj->new_proj = false;
    pObj->pDerivedObj = pDerivedObj;
    pObj->Draw = Character_draw;
    pObj->Update = Character_update;
    pObj->Interact = Character_interact;
    pObj->Destroy = Character_destory;
    _Character_load_map(pDerivedObj);
    pDerivedObj->scene = scene;
    return pObj;
}

static void handle_movement(Character *chara, Elements *ele) {
    if (key_state[ALLEGRO_KEY_A] && key_state[ALLEGRO_KEY_W]) {
        chara->dir = false;
        _Character_update_position(ele, -5, -5, chara->scene);
    } else if (key_state[ALLEGRO_KEY_A] && key_state[ALLEGRO_KEY_S]) {
        chara->dir = false;
        _Character_update_position(ele, -5, 5, chara->scene);
    } else if (key_state[ALLEGRO_KEY_D] && key_state[ALLEGRO_KEY_W]) {
        chara->dir = true;
        _Character_update_position(ele, 5, -5, chara->scene);
    } else if (key_state[ALLEGRO_KEY_D] && key_state[ALLEGRO_KEY_S]) {
        chara->dir = true;
        _Character_update_position(ele, 5, 5, chara->scene);
    } else if (key_state[ALLEGRO_KEY_A]) {
        chara->dir = false;
        _Character_update_position(ele, -5, 0, chara->scene);
    } else if (key_state[ALLEGRO_KEY_D]) {
        chara->dir = true;
        _Character_update_position(ele, 5, 0, chara->scene);
    } else if (key_state[ALLEGRO_KEY_W]) {
        _Character_update_position(ele, 0, -5, chara->scene);
    } else if (key_state[ALLEGRO_KEY_S]) {
        _Character_update_position(ele, 0, 5, chara->scene);
    }
}

void Character_update(Elements *const ele) {
    Character *chara = (Character *)(ele->pDerivedObj);
    switch (chara->state) {
    case STOP:
        if (key_state[ALLEGRO_KEY_SPACE])
            chara->state = ATK;
        else {
            handle_movement(chara, ele);
            if (chara->state == STOP)
                chara->state = MOVE;
        }
        break;
    case MOVE:
        if (key_state[ALLEGRO_KEY_SPACE])
            chara->state = ATK;
        else {
            handle_movement(chara, ele);
            if (chara->gif_status[chara->state]->done)
                chara->state = STOP;
        }
        break;
    case ATK:
        if (chara->gif_status[chara->state]->done) {
            chara->state = STOP;
            chara->new_proj = false;
        } else if (chara->gif_status[ATK]->display_index == 1) {
            chara->new_proj = false;
        } else if (chara->gif_status[ATK]->display_index == 2 && !chara->new_proj) {
            Elements *pro = New_Projectile(Projectile_L, chara->dir ? chara->x + chara->width - 100 : chara->x - 50,
                                           chara->y + 10, chara->dir ? 5 : -5);
            _Register_elements(scene, pro);
            chara->new_proj = true;
        }
        break;
    }
}

void Character_draw(Elements *const ele) {
    Character *chara = (Character *)(ele->pDerivedObj);
    ALLEGRO_BITMAP *frame = algif_get_bitmap(chara->gif_status[chara->state], al_get_time());
    if (frame)
        al_draw_bitmap(frame, chara->x, chara->y, chara->dir ? ALLEGRO_FLIP_HORIZONTAL : 0);
    if (chara->state == ATK && chara->gif_status[ATK]->display_index == 2)
        al_play_sample_instance(chara->atk_Sound);
}

void Character_destory(Elements *const ele) {
    Character *Obj = (Character *)(ele->pDerivedObj);
    al_destroy_sample_instance(Obj->atk_Sound);
    for (int i = 0; i < 3; i++)
        algif_destroy_animation(Obj->gif_status[i]);
    free(Obj->hitbox);
    free(Obj);
    free(ele);
}

void _Character_load_map(Character *character) {
    FILE *data;
    data = fopen("assets/map/gamescene_map.txt", "r");
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 16; j++)
            fscanf(data, "%d", &character->map_data[i][j]);
    fclose(data);
}
void _Character_update_position(Elements *const ele, int dx, int dy, Scene *scene) {
    Character *chara = (Character *)(ele->pDerivedObj);
    int new_x = chara->x + dx;
    int new_y = chara->y + dy;

    // 确保新位置在屏幕范围内
    if (new_x >= 0 && new_x + chara->width <= WIDTH) {
        chara->x = new_x;
        chara->hitbox->update_center_x(chara->hitbox, dx);
    }
    if (new_y >= 0 && new_y + chara->height <= HEIGHT) {
        chara->y = new_y;
        chara->hitbox->update_center_y(chara->hitbox, dy);
    }
}

// void _Character_update_position(Elements *const ele, int dx, int dy, Scene *scene) {
//     Character *chara = (Character *)(ele->pDerivedObj);
//     int new_x = chara->x + dx;
//     int new_y = chara->y + dy;
//     Floor *floor = (Floor *)(scene->ele_list[Floor_L]->ele->pDerivedObj);
//     bool collision = false;
//     /* printf("%d ", chara->map_data[0][0]);
//     printf("%d ", floor->width);*/
//     int floor_block_width = floor->width;   // / 16   // Assuming floor width is scaled by the number of blocks
//     int floor_block_height = floor->height; // / 10 Assuming floor height is scaled by the number of blocks
//     /*printf("new_x %d\n", new_x);
//     printf("new_y %d\n", new_y);
//     printf("chara width %d\n", chara->width);
//     printf("chara height %d\n", chara->height);
//     printf("floor block width %d\n", floor_block_width);
//     printf("floor block height %d\n", floor_block_height);
//     */
//     for (int i = 0; i < 10; i++) {
//         for (int j = 0; j < 16; j++) {
//             // printf("floor data %d\n", floor->map_data[i][j]);
//             if (floor->map_data[i][j] != 0) {
//                 // printf("bruh\n");
//                 int floor_x = j * floor_block_width;
//                 int floor_y = i * floor_block_height;
//                 /*
//                 printf("floor_x %d\n", floor_x);
//                 printf("floor_y %d\n", floor_y);
//                 */
//                 if ((new_x < floor_x + floor_block_width && new_x + chara->width > floor_x) &&
//                     (new_y < floor_y + floor_block_height && new_y + chara->height > floor_y)) {
//                     collision = true;
//                     // printf("COLLISION\n");
//                     break;
//                 }
//             }
//         }
//         if (collision)
//             break;
//     }
//     // printf("Collision: %d\n", collision);
//     if (collision)
//         return;
//     if (new_x >= 0 && new_x + chara->width <= WIDTH) {
//         chara->x = new_x;
//         chara->hitbox->update_center_x(chara->hitbox, dx);
//     }
//     if (new_y >= 0 && new_y + chara->height <= HEIGHT) {
//         chara->y = new_y;
//         chara->hitbox->update_center_y(chara->hitbox, dy);
//     }
//     // printf("Moved to: (%d, %d)\n", chara->x, chara->y); // Add for debugging
// }

void Character_interact(Elements *const self, Elements *const target) {
}
