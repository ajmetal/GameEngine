#include "pch.h"

#include "DebugText.h"

DebugText::DebugText(Game& game, Cache& cache, const char * key)
  : Text(game, cache, key)
{}

void DebugText::Update(float deltaTime)
{
  //std::string debugText = "fps: " + std::to_string(deltaTime * FRAMERATE);
  char buffer[256];
  snprintf(
    buffer,
    sizeof(buffer),
    "fps: %s\nright: %s\nleft: %s\nup: %s\ndown: %s",
    std::to_string(deltaTime * FRAMERATE),
    m_game.Input.rightDown ? "true" : "false",
    m_game.Input.leftDown  ? "true" : "false",
    m_game.Input.upDown    ? "true" : "false",
    m_game.Input.downDown  ? "true" : "false"
  );
  SetText(buffer);
}

DebugText::~DebugText()
{
}
