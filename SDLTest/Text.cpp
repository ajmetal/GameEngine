#include "pch.h"

#include "Text.h"

Text::Text(Game& game, Cache& cache, const char * key)
  : m_game(game)
  , m_cache(cache)
  , m_key(key)
  , m_texture(nullptr)
  , m_textColor({ 0 ,0, 0, 255 })
  , m_positions(nullptr)
  , m_text({ "" })
  , m_renderRect({ 0, 0, 0, 0 })
  , m_letterWidth(0)
{ }

bool Text::Initialize()
{
  m_texture = m_cache.GetBitmapFont(m_key, &m_fontData);
  if (m_texture == nullptr) {
    printf("Error retrieving bitmap font: %s", m_key);
    return true;
  }
  return false;
}

bool Text::Render(SDL_Renderer* renderer)
{
  m_renderRect.x = m_position.x;
  int advance = 0;
  for (auto & it : m_text) {
    LetterData * data = &m_fontData[it - ' '];
    const SDL_Rect srcRect = {
      data->pack_x, data->pack_y, data->width, data->height
    };
    m_renderRect.w = srcRect.w;
    m_renderRect.h = srcRect.h;
    m_renderRect.x += data->offset_x + advance + 1;
    m_renderRect.y = m_position.y - data->offset_y + 11;
    if (0 != SDL_RenderCopy(renderer, m_texture, &srcRect, &m_renderRect)) {
      printf("Error rendering Text %s: %s\n", m_key, SDL_GetError());
      return true;
    }
    advance = data->advance;
  }
  return false;
}

void Text::SetText(const char * text)
{
  m_text = text;
}

Text::~Text()
{}
