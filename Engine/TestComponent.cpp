#include "pch.h"
#include "TestComponent.h"

void TestComponent::Initialize()
{
    m_transform = m_owner->GetComponent<Transform>();
    m_sprite = m_owner->GetComponent<Sprite>();
}

void TestComponent::Update(const float& deltaTime)
{
    m_velocity.x = m_velocity.y = 0.0f;
    InputManager input = Game::GetInstance().m_inputManager;
    if (input.GetKeyState(SDL_SCANCODE_W)) {
        m_velocity.y = -1.0f;
        m_sprite->Play("chopperUp");
    }
    else if (input.GetKeyState(SDL_SCANCODE_S)) {
        m_velocity.y = 1.0f;
        m_sprite->Play("chopperDown");
    }
    if (input.GetKeyState(SDL_SCANCODE_D)) {
        m_velocity.x = 1.0f;
        m_sprite->Play("chopperRight");
    }
    else if (input.GetKeyState(SDL_SCANCODE_A)) {
        m_velocity.x = -1.0f;
        m_sprite->Play("chopperLeft");
    }

    if (m_velocity.x == 0.0f && m_velocity.y == 0.0f) {
        return;
    }
    glm::vec2 normalized = glm::normalize(m_velocity);
    m_velocity = normalized * 100.0f * deltaTime;
    //m_velocity = (glm::vec2)glm::normalize(m_velocity);
    m_transform->SetPosition(m_transform->GetPosition() + m_velocity);
}

TestComponent::TestComponent(Entity* owner)
    : Component(owner)
    , m_sprite(nullptr)
    , m_transform(nullptr)
    , m_acceleration(0.0)
{}

TestComponent::~TestComponent()
{
}

std::string TestComponent::ToString()
{
    return "Test Component";
}
