#pragma once

#include <iostream>

#include <vector>
#include "Entity.h";

class EntityManager
{
private:
  std::vector<Entity*> m_entities;
public:

  void Update(float deltaTime);
  void Render();
  void ClearData();
  bool HasNoEntities();
  void ListAllEntities();
  void ListAllComponents();
  Entity& AddEntity(const char* name);
  std::vector<Entity*> GetEntities() const;
  unsigned int GetEntityCount();
  EntityManager();
  ~EntityManager();
};

