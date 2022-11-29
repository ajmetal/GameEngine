#include "pch.h"
#include "PlayerControl.h"
#include "Text.h"



void PlayerControl::Initialize()
{
    m_transform = m_owner->GetComponent<Transform>();
    m_sprite = m_owner->GetComponent<Sprite>();
}

void PlayerControl::Update(const float& deltaTime)
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
    m_velocity = glm::normalize(m_velocity) * 100.0f * deltaTime;
    m_owner->GetComponent<Text>()->SetString(string_format("x: %f, y: %f", m_velocity.x, m_velocity.y).c_str());
    m_transform->SetPosition(m_transform->GetPosition() + m_velocity);
}

PlayerControl::PlayerControl(Entity* owner)
    : Component(owner)
    , m_sprite(nullptr)
    , m_transform(nullptr)
    , m_acceleration(0.0)
    , m_velocity(0.0)
{}

PlayerControl::~PlayerControl()
{
}

std::string PlayerControl::ToString()
{
    return "Test Component";
}
