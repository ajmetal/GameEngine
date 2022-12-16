#include "pch.h"
#include "BulletMover.h"
#include "Sprite.h"

/******************************************************************************
******************************************************************************/
BulletMover::BulletMover(Entity* owner)
	: Component(owner)
	, m_speed(0)
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
	//m_owner->GetComponent<Image>()->SetActive(false);
}

/******************************************************************************
******************************************************************************/
void BulletMover::Update(const float& deltaTime)
{
	Transform* transform = m_owner->GetComponent<Transform>();
	transform->SetPosition(transform->GetPosition() + m_direction * m_speed);
}

/******************************************************************************
******************************************************************************/
void BulletMover::Fire(glm::vec2 position, glm::vec2 direction, float speed)
{
	m_speed = speed;
	m_direction = glm::normalize(direction);
	m_owner->GetComponent<Transform>()->SetPosition(position);
}
