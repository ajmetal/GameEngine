#pragma once

#include "SDL.h"

#include "Game.h"
#include "EntityManager.h"
#include "Component.h"
#include "glm/glm.hpp"
#include <string>

class Transform : public Component
{
private:
  glm::vec2 m_position;
  glm::vec2 m_velocity;
  float m_width;
  float m_height;
  float m_scale;

public:
  Transform(
    float posX = 0.0f, 
    float posY = 0.0f,
    float velX = 0.0f,
    float velY = 0.0f,
    float w = 0.0f,
    float h = 0.0f,
    float s = 0.0f
  );

  inline float GetWidth() { return m_width; }
  inline float GetHeight() { return m_height; }
  inline float GetScale() { return m_scale; }
  inline glm::vec2 GetPosition() { return m_position; }
  inline glm::vec2 GetVelocity() { return m_velocity; }

  void Initialize() override;
  void Update(const float& deltaTime) override;
  void Render() override;
  void Destroy() override;
  std::string ToString() override;
  ~Transform();
};

