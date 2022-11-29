#include "Text.h"
#include "Game.h"
#include "Transform.h"

/******************************************************************************
******************************************************************************/
Text::Text(Entity* owner, const char* fontKey, const char* textString, SDL_Color color)
    : Component(owner)
    , m_key(fontKey)
    , m_textString(textString)
    , m_color(color)
    , m_ttfFont(nullptr)
    , m_rect({0,0,0,0})
    , m_texture(nullptr)
    , m_offset(0.0)
{ }

/******************************************************************************
******************************************************************************/
void Text::Initialize()
{
    m_ttfFont = Game::GetInstance().GetFont(m_key);
    SetString(m_textString.c_str());
}

/******************************************************************************
******************************************************************************/
void Text::Update(const float& deltaTime)
{
    Transform* position = m_owner->GetComponent<Transform>();
    m_rect.x = static_cast<int>(position->GetPosition().x) + m_offset.x;
    m_rect.y = static_cast<int>(position->GetPosition().y) + m_offset.y;
}

/******************************************************************************
******************************************************************************/
void Text::Render()
{
    if (0 != SDL_RenderCopy(Game::GetInstance().m_renderer, m_texture, nullptr, &m_rect)) {
        printf("SDL_RenderCopy failed for text: [%s]\n", TTF_GetError());
        return;
    }
}

/******************************************************************************
******************************************************************************/
void Text::Destroy()
{
    SDL_DestroyTexture(m_texture);
}

/******************************************************************************
******************************************************************************/
std::string Text::ToString()
{
    return "Text Component: m_textString: " + m_textString;
}

/******************************************************************************
******************************************************************************/
void Text::SetOffset(float x, float y)
{
    m_offset.x = x;
    m_offset.y = y;
}

/******************************************************************************
******************************************************************************/
void Text::SetString(const char * textString)
{
    m_textString = textString;
    SDL_Surface* surface = TTF_RenderText_Solid(m_ttfFont, m_textString.c_str(), m_color);
    if (surface == nullptr) {
        printf("returned surface was null: [%s]\n", TTF_GetError());
        return;
    }
    m_texture = SDL_CreateTextureFromSurface(Game::GetInstance().m_renderer, surface);
    if (m_texture == nullptr) {
        printf("returned texture was null: [%s]\n", TTF_GetError());
        return;
    }
    SDL_QueryTexture(m_texture, nullptr, nullptr, &m_rect.w, &m_rect.h);
    SDL_FreeSurface(surface);
}
