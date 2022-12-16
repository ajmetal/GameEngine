#include "pch.h"
#include "PlayerControl.h"
#include "Text.h"
#include "Sprite.h"

/******************************************************************************
******************************************************************************/
PlayerControl::PlayerControl(Entity* owner)
    : Component(owner)
    , m_sprite(nullptr)
    , m_transform(nullptr)
    , m_debugText(nullptr)
    , m_acceleration(0.0)
    , m_velocity(0.0)
{}

/******************************************************************************
******************************************************************************/
void PlayerControl::Initialize()
{

}

/******************************************************************************
******************************************************************************/
void PlayerControl::Start()
{
    m_transform = m_owner->GetComponent<Transform>();
    m_sprite = m_owner->GetComponent<Sprite>();
    m_debugText = m_owner->GetComponent<Text>();
    
    m_sprite->Play("chopperDown");
}

/******************************************************************************
******************************************************************************/
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

    if (input.GetMouseLeftDown()) {
        printf("Mouse left click\n");
    }

    if (m_velocity.x == 0.0f && m_velocity.y == 0.0f) {
        return;
    }
    m_velocity = glm::normalize(m_velocity) * 100.0f * deltaTime;
    m_debugText->SetString(string_format("x: %f, y: %f", m_velocity.x, m_velocity.y).c_str());
    m_transform->SetPosition(m_transform->GetPosition() + m_velocity);
}

/******************************************************************************
******************************************************************************/
PlayerControl::~PlayerControl()
{}

/******************************************************************************
******************************************************************************/
std::string PlayerControl::ToString()
{
    return "Test Component";
}
