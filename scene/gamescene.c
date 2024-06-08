#include "gamescene.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "gameover.h"
#include "sceneManager.h"

/*
   [GameScene function]
*/
Scene *New_GameScene(int label)
{
    GameScene *pDerivedObj = (GameScene *)malloc(sizeof(GameScene));
    Scene *pObj = New_Scene(label);
    // setting derived object members
    pDerivedObj->background = al_load_bitmap("assets/image/stage.jpg");
    pDerivedObj->song = al_load_sample("assets/sound/boss.mp3");
    pDerivedObj->font = al_load_ttf_font("assets/font/C.TTF", 24, 0);
    pDerivedObj->remainingTime = 0.0;
    pDerivedObj->startTime = al_get_time();
    pDerivedObj->countdownTime = 240.0; // 设置倒计时时长为120秒
    pDerivedObj->timeUp = false;

    pObj->pDerivedObj = pDerivedObj;
    // register element
    _Register_elements(pObj, New_Floor(Floor_L));
    _Register_elements(pObj, New_Beef(Beef_L));
    _Register_elements(pObj, New_Veget(Veget_L));
    _Register_elements(pObj, New_Trash(Trash_L));
    _Register_elements(pObj, New_Trash_1(Trash_1_L));
    _Register_elements(pObj, New_Teleport(Teleport_L));
    _Register_elements(pObj, New_Tree(Tree_L));
    _Register_elements(pObj, New_Character(Character_L, pObj));
    _Register_elements(pObj, New_Pan(Pan_L));
    _Register_elements(pObj, New_pot(Pot_L));
    // setting derived object function
    pObj->Update = game_scene_update;
    pObj->Draw = game_scene_draw;
    pObj->Destroy = game_scene_destroy;

    // 播放音乐
    al_play_sample(pDerivedObj->song, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);

    return pObj;
}

void game_scene_update(Scene *self)
{
    // update every element
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        allEle.arr[i]->Update(allEle.arr[i]);
    }

    // run interact for every element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        // run every interact object
        for (int j = 0; j < ele->inter_len; j++)
        {
            int inter_label = ele->inter_obj[j];
            ElementVec labelEle = _Get_label_elements(self, inter_label);
            for (int k = 0; k < labelEle.len; k++)
            {
                ele->Interact(ele, labelEle.arr[k]);
            }
        }
    }

    // remove element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        if (ele->dele)
            _Remove_elements(self, ele);
    }

    // 更新倒计时
    GameScene *gs = ((GameScene *)(self->pDerivedObj));
    double currentTime = al_get_time();
    gs->remainingTime = gs->countdownTime - (currentTime - gs->startTime);

    if (gs->remainingTime <= 0)
    {
        gs->remainingTime = 0;
        gs->timeUp = true;
        gs->timeUpStart = currentTime;
    }

    if (gs->timeUp)
    {
        // 切换到主菜单场景
        self->scene_end = true;
        printf("before end: %d", self->score);
        window = 3;
        return;
    }
    // 暂停所有元素的更新
}

// Example of increasing the score
// gs->score += 10; // Increment the score
void game_scene_draw(Scene *self)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    GameScene *gs = ((GameScene *)(self->pDerivedObj));
    al_draw_bitmap(gs->background, 0, 0, 0);
    
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }

    // 绘制倒计时器
    if (gs->timeUp)
    {
        al_draw_text(gs->font, al_map_rgb(255, 0, 0), 10, 10, 0, "Time's Up!");
    }
    else
    {
        int remainingTime = (int)gs->remainingTime;
        int minutes = remainingTime / 60;
        int seconds = remainingTime % 60;

        char timerText[20];
        snprintf(timerText, sizeof(timerText), "Time: %02d:%02d", minutes, seconds);

        al_draw_text(gs->font, al_map_rgb(255, 255, 255), 10, 10, 0, timerText);
    }

    // 绘制分数
    char scoreText[20];
    snprintf(scoreText, sizeof(scoreText), "Score: %d", self->score);

    int textWidth = al_get_text_width(gs->font, scoreText);
    int screenWidth = al_get_display_width(al_get_current_display());                                  // Get the actual screen width
    al_draw_text(gs->font, al_map_rgb(255, 255, 255), screenWidth - textWidth - 10, 10, 0, scoreText); 
    self->score+=1;
    
        
}

void game_scene_destroy(Scene *self)
{
    GameScene *Obj = ((GameScene *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background;
    ALLEGRO_SAMPLE *song = Obj->song;
    ALLEGRO_FONT *font = Obj->font;

    al_destroy_bitmap(background);
    al_destroy_sample(song);
    al_destroy_font(font);

    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Destroy(ele);
    }
    free(Obj);
    free(self);
}
