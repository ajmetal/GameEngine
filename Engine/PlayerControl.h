#pragma once
#include "Game.h"
#include "Component.h"
#include "Transform.h"
#include "Sprite.h"
#include "Text.h"

class PlayerControl : public Component
{
private:
    Transform* m_transform;
    Sprite* m_sprite;
    glm::vec2 m_velocity;
    glm::vec2 m_acceleration;
    Text* m_debugText;
    std::vector<Entity*> m_bulletPool;
    int m_lastFired = 0;
    int m_fireRate = 100;
    float m_moveSpeed = 500.0f;

public:

    void Initialize() override;
    void Start() override;
    void Update(const float& deltaTime) override;
    void Render() override {};
    void Destroy() override {};
    void OnEnable() override {};
    void OnDisable() override {};
    void SetBulletPool(std::vector<Entity*>& bulletPool);
    std::string ToString() override;
    PlayerControl(Entity* owner);
    ~PlayerControl();
};

