#include "pch.h"
#include "Animation.h"

Animation::Animation()
{
}

Animation::Animation(
    const char* sheetKey,
    const char* animationKey,
    unsigned int numFrames,
    unsigned int animationSpeed
)
    : m_key(animationKey)
    , m_index(0)
    , m_numFrames(numFrames)
    , m_animationSpeed(animationSpeed)
{
    rapidjson::Value* data = Game::s_cacheManager.GetJson(sheetKey);
    //assuming data is an array
    for (auto& i : data->GetArray()) {
        std::string name = i["name"].GetString();
        if (name.find(animationKey) != std::string::npos) {
            SDL_Rect* rect = new SDL_Rect();
            rect->x = i["x"].GetInt();
            rect->y = i["y"].GetInt();
            rect->w = i["width"].GetInt();
            rect->h = i["height"].GetInt();
            m_frames.push_back(rect);
        }
    }
}

SDL_Rect& Animation::GetFrame()
{
    return *(m_frames[m_index]);
}

bool Animation::UpdateAnimation()
{
    int nextFrame = (SDL_GetTicks() / m_animationSpeed) % m_numFrames;
    if (nextFrame != m_index) {
        m_index = nextFrame;
        return true;
    }
    return false;
}

void Animation::Initialize()
{

}


Animation::~Animation()
{
}
