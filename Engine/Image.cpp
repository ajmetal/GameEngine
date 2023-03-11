#include "Image.h"

/******************************************************************************
******************************************************************************/
Image::Image(Entity* owner, const char* key)
	: Component(owner)
	, m_key(key)
	, m_sourceRect({ 0,0,0,0 })
	, m_destinationRect({ 0,0,0,0 })
    , m_angle(0.0f)
	, m_texture(nullptr)
	, m_transform(nullptr)
    , m_flip(SDL_FLIP_NONE)
{ }

/******************************************************************************
******************************************************************************/
void Image::Start()
{
	m_transform = m_owner->GetComponent<Transform>();
	m_texture = Game::GetInstance().GetTexture(m_key);
	m_sourceRect.x = 0;
	m_sourceRect.y = 0;
	m_sourceRect.w = static_cast<int>(m_transform->GetWidth());
	m_sourceRect.h = static_cast<int>(m_transform->GetHeight());
}

/******************************************************************************
******************************************************************************/
void Image::Update(const float& deltaTime)
{
    Vector2 position = m_transform->GetPosition();
    m_destinationRect.x = static_cast<int>(position.x);
    m_destinationRect.y = static_cast<int>(position.y);
    int scale = static_cast<int>(m_transform->GetScale());
    m_destinationRect.w = static_cast<int>(m_transform->GetWidth() * scale);
    m_destinationRect.h = static_cast<int>(m_transform->GetHeight() * scale);
    m_angle = m_transform->GetRotation();
}

/******************************************************************************
******************************************************************************/
void Image::Render()
{
    if (0 != SDL_RenderCopyEx(
        Game::GetInstance().m_renderer,
        m_texture,
        &m_sourceRect,
        &m_destinationRect,
        m_angle,
        NULL,
        m_flip))
    {
        printf("Error rendering Image %s: %s\n", m_key, SDL_GetError());
    }
}
