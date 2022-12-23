#include "pch.h"
#include "EntityManager.h"


/******************************************************************************
******************************************************************************/
void EntityManager::Update(const float& deltaTime)
{
    for (auto& entity : m_entities) {
        //Entity e = *entity;
        if (entity->IsActive()) {
            entity->Update(deltaTime);
        }
    }
}

/******************************************************************************
******************************************************************************/
void EntityManager::Render()
{
    for (auto& entity : m_entities) {
        //Entity e = *entity;
        if (entity->IsActive()) {
            entity->Render();
        }
    }
}

/******************************************************************************
******************************************************************************/
void EntityManager::ClearData()
{
    for (auto& entity : m_entities) {
        entity->Destroy();
    }
}

/******************************************************************************
******************************************************************************/
bool EntityManager::HasNoEntities()
{
    return m_entities.size() == 0;
}

/******************************************************************************
******************************************************************************/
void EntityManager::ListAllEntities()
{
    for (auto& e : m_entities) {
        printf("Entity: %s\n", e->m_name);
    }
}

/******************************************************************************
******************************************************************************/
void EntityManager::ListAllComponents()
{
    printf("Components: ");
    for (auto& e : m_entities) {
        e->ListComponents();
    }
}

/******************************************************************************
******************************************************************************/
Entity* EntityManager::AddEntity(const char* name)
{
    //if (std::find(m_entities.begin(), m_entities.end(), name) != m_entities.end()) {
    //    std::string uniqueName = name;
    //    uniqueName += uniqueName[]
    //}
    Entity* e = new Entity(name);
    m_entities.push_back(e);
    return e;
}

/******************************************************************************
******************************************************************************/
Entity* EntityManager::SetEntityActive(const char* name, bool isActive)
{
    Entity* e = nullptr;
    for (int i = 0; i < m_entities.size(); ++i) {
        e = m_entities[i];
        if (e->m_name == name) {
            e->SetActive(isActive);
            break;
        }
    } 
    return e;
}

/******************************************************************************
******************************************************************************/
std::vector<Entity*> EntityManager::GetEntities() const
{
    return m_entities;
}

/******************************************************************************
******************************************************************************/
unsigned int EntityManager::GetEntityCount()
{
    return m_entities.size();
}

/******************************************************************************
******************************************************************************/
void EntityManager::Initialize()
{
    for (auto& i : m_entities) {
        i->Initialize();
    }
}

/******************************************************************************
******************************************************************************/
void EntityManager::Start()
{
    for (auto& i : m_entities) {
        i->Start();
    }
}

/******************************************************************************
******************************************************************************/
EntityManager::EntityManager()
{

}

/******************************************************************************
******************************************************************************/
EntityManager::~EntityManager()
{
    m_entities.clear();
}
