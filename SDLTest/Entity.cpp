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
    component->ToString();
  }
}

void Entity::Update(float deltaTime)
{
  for (auto& component : m_components) {
    component->Update(deltaTime);
  }
}

void Entity::Render()
{
  for (auto& component : m_components) {
    component->Render();
  }
}

void Entity::Destroy()
{
  for (auto& component : m_components) {
    component->Destroy();
  }
}

bool Entity::Initialize()
{
  return false;
}

bool Entity::IsActive() const {
  return m_isActive;
}
