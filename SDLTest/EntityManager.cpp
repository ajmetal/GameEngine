#include "pch.h"
#include "EntityManager.h"

void EntityManager::Update(const float& deltaTime)
{
  for (auto& entity : m_entities) {
    entity->Update(deltaTime);
  }
}

void EntityManager::Render()
{
  for (auto& entity : m_entities) {
    entity->Render();
  }
}

void EntityManager::ClearData()
{
  for (auto& entity : m_entities) {
    entity->Destroy();
  }
}

bool EntityManager::HasNoEntities()
{
  return m_entities.size() == 0;
}

void EntityManager::ListAllEntities()
{
  for (auto& e : m_entities) {
    printf("Entity: %s\n", e->m_name);
  }
}

void EntityManager::ListAllComponents()
{
  printf("Components: ");
  for (auto& e : m_entities) {
    e->ListComponents();
  }
}

Entity& EntityManager::AddEntity(const char * name)
{
  Entity* e = new Entity(*this, name);
  m_entities.push_back(e);
  return *e;
}

std::vector<Entity*> EntityManager::GetEntities() const
{
  return m_entities;
}

unsigned int EntityManager::GetEntityCount()
{
  return m_entities.size();
}

void EntityManager::StartScene()
{
  for (auto& i : m_entities) {
    i->Initialize();
  }
}

EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{
  m_entities.clear();
}
