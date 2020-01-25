#pragma once

class Entity;

class Component
{
public:
  Entity* m_owner;
  Component();
  virtual ~Component();
  virtual void Initialize() = 0;
  virtual void Update(float deltaTime) = 0;
  virtual void Render() = 0;
  virtual void Destroy() = 0;
  virtual void ToString();

};

