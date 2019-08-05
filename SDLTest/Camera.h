#pragma once

#include <iostream>

#include <SDL.h>

#include "GameObject.h"
#include "Game.h"

class Camera : public GameObject
{
public:
  Camera(Game & game, int x, int y, int w, int h);

  bool Initialize();
  virtual void Update(float deltaTime);
  virtual bool Render(SDL_Renderer* renderer);

  ~Camera();

private:

  SDL_Rect m_viewport;
  //SDL_Renderer * m_renderer;

  Game& m_game;

  //bool m_active;

};

