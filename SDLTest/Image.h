#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include "Game.h"
#include "Cache.h"
#include "GameObject.h"

class Image : public GameObject {
public:
  Image(Game& game, Cache& cache, const char * key);
  virtual bool Initialize();
  virtual bool Render(SDL_Renderer * renderer);
  virtual void Update(float deltaTime);
  ~Image();
protected:
private:
  SDL_Texture * m_texture;
  const char * m_key;
  Game& m_game;
  Cache m_cache;
  SDL_Rect m_rect;
};