#pragma once
#include "Game.h"
#include "Component.h"
#include "Transform.h"
#include "Sprite.h"
#include "glm/glm.hpp"

class TestComponent : public Component
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
    TestComponent();
    ~TestComponent();
};

