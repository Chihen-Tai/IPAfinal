#include "GameWindow.h"
#include "GAME_ASSERT.h"
#include "global.h"
#include "shapes/Shape.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "scene/sceneManager.h"
#include <stdbool.h>

Game *New_Game()
{
    Game *game = (Game *)malloc(sizeof(Game));
    game->execute = execute;
    game->game_init = game_init;
    game->game_update = game_update;
    game->game_draw = game_draw;
    game->game_destroy = game_destroy;
    game->title = "Kitchen Adventure";
    game->display = NULL;
    game->game_init(game);
    return game;
}

void execute(Game *self)
{
    bool run = true;
    while (run)
    {
        al_wait_for_event(event_queue, &event);
        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            run &= self->game_update(self);
            self->game_draw(self);
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            run = false;
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            key_state[event.keyboard.keycode] = true;
            break;
        case ALLEGRO_EVENT_KEY_UP:
            key_state[event.keyboard.keycode] = false;
            break;
        case ALLEGRO_EVENT_MOUSE_AXES:
            mouse.x = event.mouse.x;
            mouse.y = event.mouse.y;
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            mouse_state[event.mouse.button] = true;
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            mouse_state[event.mouse.button] = false;
            break;
        default:
            break;
        }
    }
}

void game_init(Game *self)
{
    printf("Game Initializing...\n");
    GAME_ASSERT(al_init(), "failed to initialize allegro.");

    bool addon_init = true;
    addon_init &= al_init_primitives_addon();
    addon_init &= al_init_font_addon();
    addon_init &= al_init_ttf_addon();
    addon_init &= al_init_image_addon();
    addon_init &= al_init_acodec_addon();
    addon_init &= al_install_keyboard();
    addon_init &= al_install_mouse();
    addon_init &= al_install_audio();
    GAME_ASSERT(addon_init, "failed to initialize allegro addons.");

    self->display = al_create_display(WIDTH, HEIGHT);
    GAME_ASSERT(self->display, "failed to create display.");

    create_scene(Menu_L, 0);

    event_queue = al_create_event_queue();
    GAME_ASSERT(event_queue, "failed to create event queue.");

    al_set_window_position(self->display, 0, 0);
    al_set_window_title(self->display, self->title);

    al_register_event_source(event_queue, al_get_display_event_source(self->display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    fps = al_create_timer(1.0 / FPS);
    al_register_event_source(event_queue, al_get_timer_event_source(fps));
    al_start_timer(fps);

    ALLEGRO_BITMAP *icon = al_load_bitmap("assets/image/icon.jpg");
    al_set_display_icon(self->display, icon);
}

bool game_update(Game *self)
{
    scene->Update(scene);
    if (scene->scene_end)
    {
        int temp_score = scene->score;
        scene->Destroy(scene);
        //scene->score=temp_score;
        //printf("game_update: %d", scene->score);
        switch (window)
        {
        case 0:
            create_scene(Menu_L, temp_score);
            break;
        case 1:
            create_scene(GameScene_L, temp_score);
            break;

        case -1:
            return false;
        default:
            break;
        case 2:
            create_scene(Introduction_L, temp_score);
            break;
        case 3:
            create_scene(GameOver_L, temp_score);
            break;
        }
        
    }
    return true;
}

void game_draw(Game *self) {
    al_clear_to_color(al_map_rgb(100, 100, 100));
    scene->Draw(scene);
    al_flip_display();
}

void game_destroy(Game *self) {
    al_destroy_event_queue(event_queue);
    al_destroy_display(self->display);
    scene->Destroy(scene);
    free(self);
}
