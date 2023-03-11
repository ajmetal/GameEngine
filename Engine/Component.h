#pragma once

#include <string>

class Entity;

class Component
{
public:
    Component();
    Component(Entity* owner);
    //IComponent(const IComponent&) 0;
    virtual ~Component() {};
    virtual void Initialize() = 0;
    virtual void Start() = 0;
    virtual void Update(const float& deltaTime) = 0;
    virtual void Render() = 0;
    virtual void Destroy() = 0;
    virtual std::string ToString() = 0;

    void SetActive(bool active);
    bool isActive();
    virtual void OnEnable() {};
    virtual void OnDisable() {};

protected:
    Entity* m_owner;

private:
    bool m_isActive;
};