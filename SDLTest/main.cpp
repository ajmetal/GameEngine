#include "pch.h"

#include <iostream>
#include <chrono>

#include <SDL.h>
#include <SDL_image.h>

#include "Image.h"
#include "Text.h"
#include "FpsText.h"
#include "Camera.h"
#include "Game.h"

const int WIDTH = 1280;
const int HEIGHT = WIDTH / 16 * 9;
const int SCALE_FACTOR = 4;

using namespace std;
using namespace chrono;

int main(int argc, char *argv[])
{

  Game game(WIDTH, HEIGHT);
  if (true == game.Initialize()) {
    return EXIT_FAILURE;
  }

  Cache cache;
  if (true == cache.Initialize()) {
    return EXIT_FAILURE;
  }

  //load textures
  cache.LoadImage("background", "assets/img/background.png");
  //cache.LoadFont("anon", "assets/fonts/ttf/Anonymous.ttf");
  cache.LoadBitmapFont("chocolate", "assets/fonts/bmp/chocolateMono.png", "assets/fonts/bmp/chocolateMono.json");
  //optimize them with the screen surface
  cache.FormatTexturesToScreen(game.GetRenderer(), game.GetScreen());

  //create GameObjects
  Image* background = new Image(game, cache, "background");
  Image * box = new Image(game, cache, "default");
  FpsText* fpsText = new FpsText(game, cache, "chocolate");
  //Text* inputText = new Text(game, cache, "chocolate");
  Camera* camera = new Camera(game, 0, 0, WIDTH, HEIGHT);

  //add GameObjects to the game
  game.AddObject(background);
  game.AddObject(box);
  game.AddObject(camera);
  game.AddObject(fpsText);
  //game.AddObject(inputText, 0, 16);

  bool exitSignalled = false;
  //main game loop
  while (!exitSignalled) {
    exitSignalled = game.Update();
  }

  return EXIT_SUCCESS;
}
