#pragma once
#include "Game.h"
#include "Component.h"
#include "Transform.h"

class BulletMover : public Component
{
public:
    BulletMover(Entity* owner);
    void Initialize();
    void Start();
    void Update(const float& deltaTime);
    void Render() override {};
    void Destroy() override {};
    std::string ToString() override { return ""; };

    void Fire(glm::vec2 position, glm::vec2 direction, float speed);

private:
    float m_speed;
    glm::vec2 m_direction;

};

