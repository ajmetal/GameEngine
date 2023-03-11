#pragma once

#include "SDL.h"

#include "Game.h"
#include "EntityManager.h"
#include "Component.h"
#include "glm/glm.hpp"
#include <string>

class Transform : public Component
{
public:
    Transform(
        Entity* owner = nullptr,
        float posX = 0.0f,
        float posY = 0.0f,
        float rotation = 0.0f,
        float w = 0.0f,
        float h = 0.0f,
        float s = 0.0f
    );

    inline float GetWidth() { return m_width; }
    inline float GetHeight() { return m_height; }
    inline float GetScale() { return m_scale; }
    inline glm::vec2 GetPosition() { return m_position; }
    inline float GetRotation() { return m_rotation; }
    glm::vec2 SetPosition(const glm::vec2& newPos);
    float SetRotation(float newRotation);

    void Initialize() override {};
    void Start() override {};
    void OnEnable() override {};
    void OnDisable() override {};
    void Update(const float& deltaTime) override {};
    void Render() override {};
    void Destroy() override {};
    std::string ToString() override;
    ~Transform();
private:
    glm::vec2 m_position;
    float m_width;
    float m_height;
    float m_scale;
    // rotation about the "z-axis"
    float m_rotation;

};

