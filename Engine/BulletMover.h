#pragma once
#include "Game.h"
#include "Component.h"
#include "Transform.h"
#include "Vector2.h"
#include <queue>

class BulletMover : public Component
{
public:
    BulletMover(Entity* owner, std::queue<Entity*>& pool);
    void Initialize();
    void Start();
    void Update(const float& deltaTime);
    void Render() override {};
    void Destroy() override {};
    std::string ToString() override { return ""; };

    void Fire(Vector2 position, Vector2 direction, float speed);

private:
    float m_speed;
    Vector2 m_direction;
    std::queue<Entity*>& m_pool;
};

