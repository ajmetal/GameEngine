#include "pch.h"

#include <iostream>
#include <chrono>


#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#include "Game.h"
#include "PlayerControl.h"
#include "Text.h"
#include "BulletMover.h"
#include "Image.h"

using namespace std;
using namespace chrono;

const float MS_PER_FRAME = 16.7f;
const int SCALE_FACTOR = 2;
const int WIDTH = 1920;
const int HEIGHT = 1080;

/******************************************************************************
******************************************************************************/
int main(int argc, char* argv[])
{
    //Get the singleton game instance and start setting up our "scene":
    Game::GetInstance().Initialize(MS_PER_FRAME, SCALE_FACTOR, WIDTH, HEIGHT);

    //Before the game can start, assets need to be loaded.
    Game::GetInstance().LoadSpriteSheet(
        "chopper",
        "assets/images/chopperSheet.png",
        "assets/images/chopperSheet.json"
    );

    Game::GetInstance().LoadImage("bullet", "assets/images/bullet-friendly.png");

    Entity* chopper = Game::GetInstance().AddEntity("chopper");
    chopper->AddComponent<Transform>(WIDTH / 2, HEIGHT / 2, 64, 64, 1);
    Sprite* chopperSprite = chopper->AddComponent<Sprite>("chopper");
    chopper->AddComponent<PlayerControl>();
    Text * text = chopper->AddComponent<Text>("arial", "CHOPPA!", SDL_Color{255, 255, 255, 255});
    text->SetOffset(-32, -32);

    //Entity* bullet = Game::GetInstance().AddEntity("Bullet");
    //bullet->AddComponent<Transform>();
    ////bullet->AddComponent<Image>("bullet");
    //bullet->AddComponent<BulletMover>();

    /*Entity* debugText = Game::GetInstance().AddEntity("debugText");
    debugText->AddComponent<Text>("arial");*/

    Game::GetInstance().InitializeScene();
    Game::GetInstance().StartScene();

    bool quit = false;
    while (!quit)
    {
        quit = Game::GetInstance().Update();
    }

    return EXIT_SUCCESS;
}
