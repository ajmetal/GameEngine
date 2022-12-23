#include "pch.h"

#include "Sprite.h"
#include "document.h"
#include <sstream>

/******************************************************************************
******************************************************************************/
Sprite::Sprite(Entity* owner, const char* key, const bool& isFixed)
    : Component(owner)
    , m_key(key)
    , m_isAnimating(false)
    , m_flip(SDL_FLIP_NONE)
    , m_currentAnimation(nullptr)
    , m_destinationRect({ 0,0,0,0 })
    , m_sourceRect({ 0,0,0,0 })
    , m_texture(nullptr)
    , m_transform(nullptr)
{}

/******************************************************************************
******************************************************************************/
Sprite::Sprite(Entity* owner)
    : Component(owner)
    , m_key("")
    , m_isAnimating(false)
    , m_flip(SDL_FLIP_NONE)
    , m_currentAnimation(nullptr)
    , m_destinationRect({0,0,0,0})
    , m_sourceRect({ 0,0,0,0 })
    , m_texture(nullptr)
    , m_transform(nullptr)
{}

/******************************************************************************
******************************************************************************/
void Sprite::Initialize()
{
    m_texture = Game::GetInstance().GetTexture(m_key);
    rapidjson::Value* data = Game::GetInstance().GetJson(m_key);
    if (data == nullptr) {
        printf("Could not find spritesheet named: [%s]\n", m_key);
        return;
    }
    rapidjson::GenericArray<false, rapidjson::Value> frameData = data->GetArray();
    for (int i = 0; i < frameData.Size(); ++i) {
        std::string name = frameData[i]["name"].GetString();
        std::string prefix = "";
        for (int j = 0; j < name.size(); ++j) {
            if (isdigit(name[j])) {
                prefix = name.substr(0, j);
                break;
            }
        }
        if (m_animations.find(prefix) != m_animations.end()) {
            // we already have this animation, skip next step.
            continue;
        }

        Animation* animation = new Animation();
        animation->m_key = prefix;
        for (int j = 0; j < frameData.Size(); ++j) {
            name = frameData[j]["name"].GetString();
            if (name.find(prefix) == std::string::npos) {
                continue;
            }
            SDL_Rect* rect = new SDL_Rect();
            rect->x = frameData[j]["x"].GetInt();
            rect->y = frameData[j]["y"].GetInt();
            rect->w = frameData[j]["width"].GetInt();
            rect->h = frameData[j]["height"].GetInt();
            animation->m_frames.push_back(rect);
            animation->m_numFrames++;
            animation->m_animationSpeed = 50;
        }
        m_animations[animation->m_key] = animation;
    }
}

/******************************************************************************
******************************************************************************/
void Sprite::Start()
{
    m_transform = m_owner->GetComponent<Transform>();
    m_sourceRect.x = 0;
    m_sourceRect.y = 0;
    m_sourceRect.w = static_cast<int>(m_transform->GetWidth());
    m_sourceRect.h = static_cast<int>(m_transform->GetHeight());
   
}

//Sprite* Sprite::AddAnimation(const char* key, const int& numFrames, const int& animationSpeed)
//{
//    Animation* anim = new Animation(m_key, key, numFrames, animationSpeed);
//    m_animations[key] = anim;
//    m_isAnimated = true;
//    return this;
//}

/******************************************************************************
******************************************************************************/
void Sprite::Play(const std::string& animationName)
{
    if (m_animations.find(animationName) == m_animations.end()) {
        printf("animation not found: [%s]\n", animationName.c_str());
        return;
    }
    m_currentAnimation = m_animations[animationName];
    m_isAnimating = true;
}

/******************************************************************************
******************************************************************************/
void Sprite::Destroy()
{
}

/******************************************************************************
******************************************************************************/
void Sprite::Update(const float& deltaTime)
{
    if (m_isAnimating && m_currentAnimation != nullptr)
    {
        int nextFrame = (SDL_GetTicks() / m_currentAnimation->m_animationSpeed) % m_currentAnimation->m_numFrames;
        if (nextFrame != m_currentAnimation->m_currentFrame) {
            m_currentAnimation->m_currentFrame = nextFrame;
            SDL_Rect* frame = m_currentAnimation->m_frames[m_currentAnimation->m_currentFrame];
            m_sourceRect.x = frame->x;
            m_sourceRect.y = frame->y;
            m_sourceRect.w = frame->w;
            m_sourceRect.h = frame->h;
        }
    }

    glm::vec2 position = m_transform->GetPosition();
    m_destinationRect.x = static_cast<int>(position.x);
    m_destinationRect.y = static_cast<int>(position.y);
    int scale = static_cast<int>(m_transform->GetScale());
    m_destinationRect.w = static_cast<int>(m_transform->GetWidth() * scale);
    m_destinationRect.h = static_cast<int>(m_transform->GetHeight() * scale);
}

/******************************************************************************
******************************************************************************/
void Sprite::Render()
{
    if (0 != SDL_RenderCopyEx(
        Game::GetInstance().m_renderer,
        m_texture,
        &m_sourceRect,
        &m_destinationRect,
        0.0,
        NULL,
        m_flip))
    {
        printf("Error rendering Image %s: %s\n", m_key, SDL_GetError());
    }
}

/******************************************************************************
******************************************************************************/
std::string Sprite::ToString()
{
    std::stringstream ss;
    ss << "Sprite: Animations:";
    for (auto& i : m_animations) {
        ss << i.second->m_key << ", ";
    }
    return ss.str();
}

/******************************************************************************
******************************************************************************/
Sprite::~Sprite()
{
}
