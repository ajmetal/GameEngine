#pragma once
#include "Game.h"
#include "Component.h"
#include "Transform.h"
#include "Sprite.h"

class PlayerControl : public Component
{
private:
    Transform* m_transform;
    Sprite* m_sprite;
    glm::vec2 m_velocity;
    glm::vec2 m_acceleration;

public:

    void Initialize() override;
    void Update(const float& deltaTime) override;
    void Render() override {};
    void Destroy() override {};
    std::string ToString() override;
    PlayerControl(Entity* owner);
    ~PlayerControl();
};

