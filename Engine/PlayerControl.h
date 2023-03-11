#pragma once
#include "Game.h"
#include "Component.h"
#include "Transform.h"
#include "Sprite.h"
#include "Text.h"
#include <queue>

class PlayerControl : public Component
{

public:

    void Initialize() override;
    void Start() override;
    void Update(const float& deltaTime) override;
    void Render() override {};
    void Destroy() override {};
    void OnEnable() override {};
    void OnDisable() override {};
    std::string ToString() override;
    PlayerControl(Entity* owner, std::queue<Entity*>& pool);
    ~PlayerControl();

private:
    Transform* m_transform;
    Sprite* m_sprite;
    Vector2 m_velocity;
    Vector2 m_acceleration;
    Text* m_debugText;
    std::queue<Entity*>& m_bulletPool;
    int m_lastFired = 0;
    int m_fireRate = 100;
    float m_moveSpeed = 500.0f;
};

