#ifndef GAMESCENE_H_INCLUDED
#define GAMESCENE_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_font.h>
#include "../element/element.h"
#include "../element/charater.h"
#include "../element/floor.h"
#include "../element/teleport.h"
#include "../element/tree.h"
#include "../element/projectile.h"
#include "../element/beef.h"
#include "../element/trash.h"
#include "../element/veget.h"
#include "../element/trash_1.h"
#include "../element/pan.h"
#include "../element/pot.h"
/*
   [game scene object]
*/
typedef enum EleType
{
    Floor_L,
    Teleport_L,
    Tree_L,
    Character_L,
    Projectile_L,
    FloorRow_L,
    Beef_L,
    Veget_L,
    Trash_L,
    Trash_1_L,
    Pan_L,
    Pot_L
} EleType;
typedef struct _GameScene
{
    ALLEGRO_BITMAP *background;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_FONT *font;
    double startTime;
    double countdownTime;  // 倒计时时间
    double remainingTime;  // 剩余时间
    bool timeUp; 
    double timeUpStart;    // Time's Up开始时间
    int score;
} GameScene;
Scene *New_GameScene(int label);
void game_scene_update(Scene *self);
void game_scene_draw(Scene *self);
void game_scene_destroy(Scene *self);

#endif
