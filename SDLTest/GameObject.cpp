#include "pch.h"

#include "GameObject.h"

GameObject::GameObject()
  : m_id(currentId++)
  , m_position{0, 0}
  , m_scale{0, 0}
{ }

void GameObject::SetPosition(const float& x, const float& y)
{
  m_position.x = x;
  m_position.y = y;
}

void GameObject::SetPosition(const glm::vec2& point)
{
  m_position = point;
}

