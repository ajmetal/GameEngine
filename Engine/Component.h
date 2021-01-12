#pragma once

#include <string>

class Entity;

class IComponent
{
public:
    Entity* m_owner;
    IComponent();
    IComponent(const IComponent&) = delete;
    virtual ~IComponent() = 0;
    virtual void Initialize() = 0;
    virtual void Update(const float& deltaTime) = 0;
    virtual void Render() = 0;
    virtual void Destroy() = 0;
    virtual std::string ToString() = 0;
};

