#include "pch.h"
#include "Transform.h"

Transform::Transform(
  float posX, 
  float posY, 
  float velX, 
  float velY, 
  float w, 
  float h, 
  float s
)
  //Component(nullptr)
  : m_position(glm::vec2(posX, posY))
  , m_velocity(glm::vec2(velX, velY))
  , m_width(w)
  , m_height(h)
  , m_scale(s)
{
}

void Transform::Initialize()
{
}

void Transform::Update(const float& deltaTime)
{
  float speed = 100;
  m_velocity.x = m_velocity.y = 0;
  if (Game::s_inputManager.GetKeyState(SDLK_w)) {
    m_velocity.y = -speed;
  }
  else if (Game::s_inputManager.GetKeyState(SDLK_s)) {
    m_velocity.y = speed;
  }
  if (Game::s_inputManager.GetKeyState(SDLK_d)) {
    m_velocity.x = speed;
  }
  else if (Game::s_inputManager.GetKeyState(SDLK_a)) {
    m_velocity.y = -speed;
  }

  m_position.x += m_velocity.x * deltaTime;
  m_position.y += m_velocity.y * deltaTime;
}

void Transform::Render()
{
  //SDL_Rect transformRect = {
  //  m_position.x,
  //  m_position.y,
  //  m_width,
  //  m_height
  //};

  //SDL_SetRenderDrawColor(Game::s_renderer, 255, 255, 255, 255);
  //SDL_RenderFillRect(Game::s_renderer, &transformRect);
}

void Transform::Destroy()
{
}

std::string Transform::ToString()
{
  char buffer[256];
  snprintf(
    buffer,
    sizeof(buffer),
    "Transform on %s: posX: %f, posY: %f, velX: %f, velY: %f, w: %f, h: %f, s: %f\n",
    m_owner->m_name,
    m_position.x,  
    m_position.y,
    m_velocity.x,
    m_velocity.y,
    m_width,
    m_height,
    m_scale
  );
  return buffer;
}

Transform::~Transform()
{
}
