#include "pch.h"

#include <iostream>
#include <chrono>

#include <SDL.h>
#include <SDL_image.h>

#include "Game.h"
#include "Entity.h"
#include "Transform.h"
#include "Sprite.h"
#include "TestComponent.h"

const int WIDTH = 800;
const int HEIGHT = 600;
const int SCALE_FACTOR = 2;

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
  a.AddComponent<Transform>(0, 0, 32, 32, SCALE_FACTOR);
  std::cout << a.GetComponent<Transform>()->GetHeight() << std::endl;
  Sprite* s = a.AddComponent<Sprite>("chopperSheet");
  s->AddAnimation("chopperDown", 2, 10)->
    AddAnimation("chopperRight", 2, 10)->
    AddAnimation("chopperLeft", 2, 10)->
    AddAnimation("chopperUp", 2, 10);
  s->Play("chopperDown");
  a.AddComponent<TestComponent>();
  //a.GetComponent<Sprite>().AddAnimation("chopperDown", 2, 10);
  //a.GetComponent<Sprite>().Play("chopperDown");

  game.StartScene();
 
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
