#include "pch.h"
#include "Entity.h"

Entity::Entity()
    : m_name("")
    , m_isActive(false)
{ }

Entity::Entity(const char* name)
    : m_name(name)
    , m_isActive(false)
{ }

Entity::Entity(Entity& other)
    : m_isActive(other.m_isActive)
    , m_name(other.m_name)
    , m_components(other.m_components)
{ }

//Entity(Entity&&);

void Entity::operator=(Entity& other)
{
    //this->m_manager = other.m_manager;
    this->m_isActive = other.m_isActive;
    this->m_name = other.m_name;
    this->m_components = other.m_components;
}

//void operator=(Entity&&);

Entity::~Entity()
{
    Destroy();
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
