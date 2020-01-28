#pragma once

#include <string>

class Entity;

class Component
{
public:
  Entity* m_owner;
  Component();
  Component(const Component&) = delete;
  virtual ~Component();
  virtual void Initialize() = 0;
  virtual void Update(const float& deltaTime) = 0;
  virtual void Render() = 0;
  virtual void Destroy() = 0;
  virtual std::string ToString();
};

