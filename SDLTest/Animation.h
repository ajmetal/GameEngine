#pragma once

#include <vector>
#include <unordered_map>
#include <SDL.h>
#include "Game.h"

class Animation
{
private:
  std::vector<SDL_Rect*> m_frames;
public:
  const char* m_key;
  unsigned int m_index;
  unsigned int m_numFrames;
  unsigned int m_animationSpeed;

  SDL_Rect& GetFrame();
  //returns whether the animation frame has changed
  bool UpdateAnimation();

  Animation();
  Animation(
    const char* sheetKey, 
    const char* animationKey, 
    unsigned int numFrames, 
    unsigned int animationSpeed
  );
  void Initialize();
  ~Animation();
};

