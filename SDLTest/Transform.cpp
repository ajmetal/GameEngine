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

void Transform::Update(float deltaTime)
{
  m_position.x += m_velocity.x * deltaTime;
  m_position.y += m_velocity.y * deltaTime;
}

void Transform::Render()
{
  SDL_Rect transformRect = {
    m_position.x,
    m_position.y,
    m_width,
    m_height
  };

  SDL_SetRenderDrawColor(Game::s_renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(Game::s_renderer, &transformRect);
}

void Transform::Destroy()
{
}

void Transform::ToString()
{
  printf("Transform on %s: posX: %f, posY: %f, velX: %f, velY: %f, w: %f, h: %f, s: %f\n",
    m_owner->m_name,
    m_position.x,  
    m_position.y,
    m_velocity.x,
    m_velocity.y,
    m_width,
    m_height,
    m_scale
  );
}

Transform::~Transform()
{
}
