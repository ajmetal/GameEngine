#pragma once

//#include <vector>
#include <typeinfo>
#include <map>

#include "Component.h"
#include <iostream>

class EntityManager;

class Entity
{
private:
  EntityManager& m_manager;
  std::map<const std::type_info*, Component*> m_components;
  bool m_isActive;

public:
  const char * m_name;

  void ListComponents();

  template<typename T, typename ...TArgs>
  T& AddComponent(TArgs && ...args)
  {
    T* component = new T(std::forward<TArgs>(args)...);
    component->m_owner = this;
    //m_components.push_back(component);
    m_components[&typeid(*component)] = component;
    component->Initialize();
    return *static_cast<T*>(component);
  }

  template <typename T>
  T& GetComponent() {
    return *static_cast<T*>(m_components[&typeid(T)]);
  }

  template <typename T>
  bool HasComponent() {
    return (m_components.find(&typeid(T)) != m_components.end());
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

