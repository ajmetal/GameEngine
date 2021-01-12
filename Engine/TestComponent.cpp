#include "pch.h"
#include "TestComponent.h"

void TestComponent::Initialize()
{
    m_transform = m_owner->GetComponent<Transform>();
    m_sprite = m_owner->GetComponent<Sprite>();
}

void TestComponent::Update(const float& deltaTime)
{
    float speed = 100;
    m_velocity.x = m_velocity.y = 0;
    if (Game::s_inputManager.GetKeyState(SDLK_w)) {
        m_velocity.y = -speed;
    }
    else if (Game::s_inputManager.GetKeyState(SDLK_s)) {
        m_velocity.y = speed;
    }
    if (Game::s_inputManager.GetKeyState(SDLK_d)) {
        m_velocity.x = speed;
    }
    else if (Game::s_inputManager.GetKeyState(SDLK_a)) {
        m_velocity.x = -speed;
    }

    glm::vec2 position = m_transform->GetPosition();
    m_transform->SetPosition(position + (m_velocity * deltaTime));
}

TestComponent::TestComponent()
{

}


TestComponent::~TestComponent()
{
}
