#include "pch.h"
#include "Entity.h"

Entity::Entity(EntityManager & manager)
  : m_manager(manager)
  , m_isActive(false)
{
}

Entity::Entity(EntityManager & manager, const char * name)
  : m_manager(manager)
  , m_name(name)
  , m_isActive(false)
{ 
}

Entity::~Entity()
{
}

void Entity::ListComponents()
{
  for (auto& component : m_components) {
    std::cout << component.second->ToString() << std::endl;
  }
}

void Entity::Update(const float& deltaTime)
{
  for (auto& component : m_components) {
    component.second->Update(deltaTime);
  }
}

void Entity::Render()
{
  for (auto& component : m_components) {
    component.second->Render();
  }
}

void Entity::Destroy()
{
  for (auto& component : m_components) {
    component.second->Destroy();
  }
}

bool Entity::Initialize()
{
  for (auto& i : m_components) {
    i.second->Initialize();
  }
  return false;
}

bool Entity::IsActive() const {
  return m_isActive;
}
