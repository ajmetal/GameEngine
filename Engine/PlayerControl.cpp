#include "pch.h"
#include "PlayerControl.h"
#include "Text.h"
#include "Sprite.h"
#include "Image.h"
#include "BulletMover.h"

/******************************************************************************
******************************************************************************/
PlayerControl::PlayerControl(Entity* owner, std::queue<Entity*>& pool)
    : Component(owner)
    , m_sprite(nullptr)
    , m_transform(nullptr)
    , m_debugText(nullptr)
    , m_acceleration({0.0f, 0.0f})
    , m_velocity({0.0f, 0.0f})
    , m_bulletPool(pool)
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
    m_transform->SetRotation(m_transform->GetRotation() + 1.0f);
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

    auto ticks = SDL_GetTicks();

    if (input.GetMouseLeftDown() && ticks > m_lastFired + m_fireRate) {
        m_lastFired = ticks;
        if (m_bulletPool.size() != 0) {
            Entity* b = m_bulletPool.front();
            m_bulletPool.pop();
            Vector2 mousePos = { (float)input.GetMouseX(), (float)input.GetMouseY() };
            Vector2 playerPos = m_transform->GetPosition();
            BulletMover* mover = b->GetComponent<BulletMover>();
            mover->Fire(playerPos, mousePos - playerPos, 20);
        }
    }
    m_velocity = m_velocity.Normalized() * m_moveSpeed * deltaTime;
    m_debugText->SetString(string_format("rotation: %f", m_transform->GetRotation()).c_str());
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
