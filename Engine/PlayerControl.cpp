#include "pch.h"
#include "PlayerControl.h"
#include "Text.h"
#include "Sprite.h"
#include "Image.h"
#include "BulletMover.h"

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
void PlayerControl::SetBulletPool(std::vector<Entity*>& bulletPool)
{
    m_bulletPool = bulletPool;
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

    auto ticks = SDL_GetTicks();

    if (input.GetMouseLeftDown() && ticks > m_lastFired + m_fireRate) {
        m_lastFired = ticks;
        for (int i = 0; i < m_bulletPool.size(); ++i) {
            Entity* b = m_bulletPool[i];
            if (b->IsActive() == false) {
                glm::vec2 mousePos = { input.GetMouseX(), input.GetMouseY() };
                glm::vec2 playerPos = m_transform->GetPosition();
                b->GetComponent<BulletMover>()->Fire(playerPos, mousePos - playerPos, 20);
                break;
            }
        }
    }

    if (m_velocity.x == 0.0f && m_velocity.y == 0.0f) {
        return;
    }
    m_velocity = glm::normalize(m_velocity) * m_moveSpeed * deltaTime;
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
