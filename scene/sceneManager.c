#include "sceneManager.h"
#include "menu.h"
#include "gamescene.h"
#include "introscene.h"
#include "gameover.h"
Scene *scene = NULL;
void create_scene(SceneType type, int temp_score)
{
    switch (type)
    {
    case Menu_L:
        scene = New_Menu(Menu_L);
        break;
    case GameScene_L:
        scene = New_GameScene(GameScene_L);
        break;
    case Introduction_L:
        scene = New_Introduction(Introduction_L);
        break;
    case GameOver_L:
        printf("SceneManager Score: %d\n", scene->score);
        scene = New_GameOver(GameOver_L, temp_score);
        break;
    default:
        break;
    }
}