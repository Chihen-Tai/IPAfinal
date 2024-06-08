#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "element.h"
#include "../shapes/Shape.h"
#include "../scene/gamescene.h"
#include "../algif5/src/algif.h"
#include <stdbool.h>
#include "floor.h"

/*
   [character object]
*/
typedef enum CharacterType {
    STOP = 0,
    MOVE,
    ATK
} CharacterType;

typedef struct _Character {
    int x, y;
    int width, height;              // the width and height of image
    bool dir;                       // true: face to right, false: face to left
    int state;                      // the state of character
    ALGIF_ANIMATION *gif_status[3]; // gif for each state. 0: stop, 1: move, 2:attack
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    int anime;      // counting the time of animation
    int anime_time; // indicate how long the animation
    bool new_proj;
    Shape *hitbox;                  // the hitbox of object
    int map_data[10][16];           // character's map data, if applicable
    Scene *scene;
} Character;



Elements *New_Character(int label, Scene *scene);
void _Character_update_position(Elements *self, int dx, int dy, Scene *scene);
void Character_update(Elements *self);
void Character_interact(Elements *self, Elements *target);
void Character_draw(Elements *self);
void Character_destory(Elements *self);
void _Character_load_map(Character *character);

#endif