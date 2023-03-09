#pragma once

#include "Component.h"
#include <queue>

class ObjectPool : public Component
{
public:
    ObjectPool(Entity* owner);
    virtual ~ObjectPool();
    virtual void Initialize();
    virtual void Start();
    virtual void Update(const float& deltaTime);
    virtual void Render() {};
    virtual void Destroy();
    virtual std::string ToString();
private:
    unsigned int m_size;
    std::queue<Entity*> m_pool;
};

