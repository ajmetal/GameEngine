#pragma once

#include "Text.h"

class DebugText : public Text
{
public:
  DebugText(Game& game, Cache& cache, const char * key);
  virtual void Update(float deltaTime);
  ~DebugText();
};

