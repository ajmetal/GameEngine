#pragma once

#include <vector>

#include "Component.h"

class EntityManager;

class Entity
{
private:
  EntityManager& m_manager;
  std::vector<Component*> m_components;
  bool m_isActive;

public:
  const char * m_name;

  void ListComponents();

  template<typename T, typename ...TArgs>
  T& AddComponent(TArgs && ...args)
  {
    T* component = new T(std::forward<TArgs>(args)...);
    component->m_owner = this;
    m_components.push_back(component);
    component->Initialize();
    return *component;
  }


  void Update(float deltaTime);
  void Render();
  void Destroy();
  bool Initialize();
  Entity(EntityManager& manager);
  Entity(EntityManager& manager, const char* name);
  bool IsActive() const;
  virtual ~Entity();

};

