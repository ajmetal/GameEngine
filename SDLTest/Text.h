#pragma once
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Image.h"
#include "Game.h"
#include "Cache.h"

class Text : public GameObject
{
public:
  Text(Game& game, Cache& cache, const char * key);
  virtual bool Initialize();
  virtual void Update(float deltaTime) = 0;
  virtual bool Render(SDL_Renderer* renderer);
  void SetText(const char * text);
  virtual ~Text();

protected:
  std::string m_text;
  Game& m_game;
  Cache& m_cache;
  const char * m_key;

private:
  SDL_Texture* m_texture;
  int m_letterWidth;
  SDL_Color m_textColor;
  LetterData* m_fontData;
  SDL_Rect m_renderRect;
  SDL_Rect* m_positions;

};

