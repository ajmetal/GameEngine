#include "pch.h"

#include <iostream>
#include <chrono>

#include <SDL.h>
#include <SDL_image.h>

#include "Game.h"
#include "Entity.h"
#include "Transform.h"
#include "Sprite.h"

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

  Game::s_cacheManager.LoadSpriteSheet("chopperSheet", "./assets/images/chopperSheet.png", "./assets/images/chopperSheet.json");
  Game::s_cacheManager.FormatTexturesToScreen(Game::s_renderer, game.GetScreen());

  Entity& a(game.AddEntity("A"));
  a.AddComponent<Transform>(0, 0, 20, 20, 32, 32, 1);
  std::cout << a.GetComponent<Transform>().GetHeight() << std::endl;
  a.AddComponent<Sprite>("chopperSheet");
  
  a.GetComponent<Sprite>().AddAnimation("chopperDown", 2, 1000);
  a.GetComponent<Sprite>().Play("chopperDown");
 
  std::cout << (a.HasComponent<Sprite>() ? "true" : "false") << std::endl;

  game.ListAllEntities();
  game.ListAllComponents();

  bool exitSignalled = false;
  //main game loop
  while (!exitSignalled) {
    exitSignalled = game.Update();
  }

  return EXIT_SUCCESS;
}
