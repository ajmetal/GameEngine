#include "pch.h"

#include <iostream>
#include <chrono>


#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#include "Game.h"
#include "TestComponent.h"
#include "Text.h"

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

    Entity* chopper = Game::GetInstance().AddEntity("chopper");
    chopper->AddComponent<Transform>(WIDTH / 2, HEIGHT / 2, 64, 64, 1);
    Sprite* chopperSprite = chopper->AddComponent<Sprite>("chopper");
    chopper->AddComponent<TestComponent>();
    //chopper->AddComponent<Text>("arial", "CHOPPA!");

    Game::GetInstance().StartScene();
    chopperSprite->Play("chopperDown");

    //Once initialize is called, all components/entities/etc will be initialized,
    //so the "scene" needs to be totally set up before Intitialize is called.
    bool quit = false;
    while (!quit)
    {
        quit = Game::GetInstance().Update();
    }

    return EXIT_SUCCESS;
}
