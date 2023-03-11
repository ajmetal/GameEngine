#include "pch.h"
#include "BulletMover.h"
#include "Sprite.h"
#include "Image.h"

/******************************************************************************
******************************************************************************/
BulletMover::BulletMover(Entity* owner, std::queue<Entity*>& pool)
	: Component(owner)
	, m_speed(0)
	, m_pool(pool)
	, m_direction(0.0,0.0)
{}

/******************************************************************************
******************************************************************************/
void BulletMover::Initialize()
{
	
}

/******************************************************************************
******************************************************************************/
void BulletMover::Start()
{
	m_owner->SetActive(false);
}

/******************************************************************************
******************************************************************************/
void BulletMover::Update(const float& deltaTime)
{
	Transform* transform = m_owner->GetComponent<Transform>();
	transform->SetPosition(transform->GetPosition() + m_direction * m_speed);
	glm::vec2 position = transform->GetPosition();
	int w, h;
	SDL_GetWindowSize(Game::GetInstance().m_window, &w, &h);
	if (position.x < 0 || position.x > w || position.y < 0 || position.y > h) {
		m_owner->SetActive(false);
		m_pool.push(m_owner);
	}
}

/******************************************************************************
******************************************************************************/
void BulletMover::Fire(glm::vec2 position, glm::vec2 direction, float speed)
{
	m_speed = speed;
	m_direction = glm::normalize(direction);
	m_owner->GetComponent<Transform>()->SetPosition(position);
	m_owner->SetActive(true);
}
