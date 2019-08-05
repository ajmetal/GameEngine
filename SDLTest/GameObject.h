#pragma once

#include <SDL.h>
#include "Vector2.h"

 static int currentId = 0;

class GameObject
{
public:

  virtual bool Initialize() = 0;
  virtual void Update(float deltaTime) = 0;
  virtual bool Render(SDL_Renderer* renderer) = 0;
  inline int GetId() { return m_id; }
  inline bool IsActive() { return m_active; }
  virtual void SetPosition(const float& x, const float& y);
  virtual void SetPosition(const Vector2& point);
protected:
  GameObject();
  //~GameObject();
  Vector2 m_position;
  int m_id;
  bool m_active;
  Vector2 m_scale;

private:


};

