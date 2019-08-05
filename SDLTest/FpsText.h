#pragma once

#include "Text.h"

class FpsText : public Text
{
public:
  FpsText(Game& game, Cache& cache, const char * key);
  virtual void Update(float deltaTime);
  ~FpsText();
};

