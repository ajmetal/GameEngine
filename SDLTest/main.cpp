#include "pch.h"

#include <iostream>
#include <chrono>

#include <SDL.h>
#include <SDL_image.h>

#include "Image.h"
#include "Text.h"
#include "DebugText.h"
#include "Camera.h"
#include "Game.h"
#include "Entity.h"
#include "Transform.h"

const int WIDTH = 800;
const int HEIGHT = 600;
//const int SCALE_FACTOR = 4;

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

  Entity& a(game.AddEntity("A"));
  a.AddComponent<Transform>(0, 0, 20, 20, 32, 32, 1);

  Entity& b(game.AddEntity("B"));
  b.AddComponent<Transform>(WIDTH / 2, HEIGHT / 2, 20, -20, 32, 32, 1);

  Entity& c(game.AddEntity("C"));
  c.AddComponent<Transform>(WIDTH, HEIGHT, -20, -20, 32, 32, 1);

  game.ListAllEntities();
  game.ListAllComponents();

  bool exitSignalled = false;
  //main game loop
  while (!exitSignalled) {
    exitSignalled = game.Update();
  }

  return EXIT_SUCCESS;
}
