#pragma once

#include <string>

//#include "Entity.h"

class Entity;

class Component
{
public:
    Component()
    : m_owner(nullptr)
    {};
    Component(Entity* owner)
        : m_owner(owner)
    {};
    //IComponent(const IComponent&) 0;
    virtual ~Component() {};
    virtual void Initialize() = 0;
    virtual void Update(const float& deltaTime) = 0;
    virtual void Render() = 0;
    virtual void Destroy() = 0;
    virtual std::string ToString() = 0;

protected:
    Entity* m_owner;

private:
};

