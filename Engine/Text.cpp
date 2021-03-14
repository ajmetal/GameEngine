#include "Text.h"
#include "Game.h"

Text::Text(const char* fontKey, const char* textString, SDL_Color color)
    : m_key(fontKey)
    , m_textString("")
    , m_color(color)
    , m_ttfFont(nullptr)
{ }

/******************************************************************************
******************************************************************************/
void Text::Initialize()
{
    m_ttfFont = Game::GetInstance().GetFont(m_key);
}

/******************************************************************************
******************************************************************************/
void Text::Update(const float& deltaTime)
{
}

/******************************************************************************
******************************************************************************/
void Text::Render()
{
    SDL_Surface* textSurface = TTF_RenderUTF8_Solid(m_ttfFont, m_textString.c_str(), m_color);
    if (textSurface == nullptr) {
        printf("returned surface was null: [%s]\n", TTF_GetError());
        return;
    }
    SDL_BlitSurface(textSurface, NULL, Game::GetInstance().m_screen, NULL);
    //perhaps we can reuse it, but I assume not for simplicity.
    SDL_FreeSurface(textSurface);
}

/******************************************************************************
******************************************************************************/
void Text::Destroy()
{
}

/******************************************************************************
******************************************************************************/
std::string Text::ToString()
{
    return "Text Component: m_textString: " + m_textString;
}

/******************************************************************************
******************************************************************************/
void Text::SetString(const char * textString)
{
    m_textString = textString;
}
