#include "pch.h"

#include "FpsText.h"

FpsText::FpsText(Game& game, Cache& cache, const char * key)
  : Text(game, cache, key)
{}

void FpsText::Update(float deltaTime)
{
  std::string fps = "fps: " + std::to_string(deltaTime * FRAMERATE);
  SetText(fps.c_str());
}

FpsText::~FpsText()
{
}
