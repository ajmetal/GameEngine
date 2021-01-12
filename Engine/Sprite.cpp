#include "pch.h"

#include "Sprite.h"
#include <sstream>

Sprite::Sprite(const char* key, const bool& isFixed)
    : m_key(key)
    , m_isAnimated(false)
    , m_isFixed(isFixed)
    , m_flip(SDL_FLIP_NONE)
    , m_currentAnimation(nullptr)
    //, m_transform(nullptr)
{}

void Sprite::Initialize()
{
    m_transform = m_owner->GetComponent<Transform>();
    m_texture = Game::s_cacheManager.GetTexture(m_key);
    m_sourceRect.x = 0;
    m_sourceRect.y = 0;
    m_sourceRect.w = static_cast<int>(m_transform->GetWidth());
    m_sourceRect.h = static_cast<int>(m_transform->GetHeight());
}

Sprite* Sprite::AddAnimation(const char* key, const int& numFrames, const int& animationSpeed)
{
    Animation* anim = new Animation(m_key, key, numFrames, animationSpeed);
    m_animations[key] = anim;
    m_isAnimated = true;
    return this;
}

Sprite* Sprite::Play(const char* animationName)
{
    m_currentAnimation = m_animations[animationName];
    return this;
}

void Sprite::Destroy()
{
}

void Sprite::Update(const float& deltaTime)
{
    if (m_isAnimated &&
        m_currentAnimation != nullptr &&
        m_currentAnimation->UpdateAnimation())
    {
        SDL_Rect frame = m_currentAnimation->GetFrame();
        m_sourceRect.x = frame.x;
        m_sourceRect.y = frame.y;
        m_sourceRect.w = frame.w;
        m_sourceRect.h = frame.h;
    }
    glm::vec2 position = m_transform->GetPosition();
    m_destinationRect.x = static_cast<int>(position.x);
    m_destinationRect.y = static_cast<int>(position.y);
    int scale = static_cast<int>(m_transform->GetScale());
    m_destinationRect.w = static_cast<int>(m_transform->GetWidth() * scale);
    m_destinationRect.h = static_cast<int>(m_transform->GetHeight() * scale);
}

void Sprite::Render()
{
    if (0 != SDL_RenderCopyEx(
        Game::s_renderer,
        m_texture,
        &m_sourceRect,
        &m_destinationRect,
        0.0,
        NULL,
        m_flip)
        ) {
        printf("Error rendering Image %s: %s\n", m_key, SDL_GetError());
        //return true;
    }
    //return false;
}

std::string Sprite::ToString()
{
    std::stringstream ss;
    ss << "Sprite: Animations:";
    for (auto& i : m_animations) {
        ss << i.second->m_key << ", ";
    }
    return ss.str();
}

Sprite::~Sprite()
{
}
