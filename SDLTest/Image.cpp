#include "pch.h"

#include "Image.h";

Image::Image(Game& game, Cache& cache, const char* key)
  : m_game(game)
  , m_cache(cache)
  , m_key(key)
  , m_texture(nullptr)
  , m_rect({ 0, 0, 0, 0 })
{ }

bool Image::Initialize()
{
  //Image is not responsible to freeing this memory, it's handled by the Cache
  m_texture = m_cache.GetTexture(m_key);
  if (nullptr == m_texture) {
    printf("Error retrieving texture: %s", m_key);
    return true;
  }
  //set this rect to the width and height of the original image
  SDL_QueryTexture(m_texture, NULL, NULL, &m_rect.w, &m_rect.h);
  return false;
}

void Image::Update(float deltaTime)
{
  //debugging
  float speed = 200 * deltaTime;
  if (m_game.Input.leftDown) {
    m_position.x -= speed;
  }
  else if (m_game.Input.rightDown) {
    m_position.x += speed;
  }
  if (m_game.Input.downDown) {
   m_position.y += speed;
  }
  else if (m_game.Input.upDown) {
    m_position.y -= speed;
  }
}

bool Image::Render(SDL_Renderer * renderer)
{
  m_rect.x = m_position.x;
  m_rect.y = m_position.y;
  //was there an error?
  if (0 != SDL_RenderCopy(renderer, m_texture, NULL, &m_rect)) {
    printf("Error rendering Image %s: %s\n", m_key, SDL_GetError());
    return true;
  }
  return false;
}

Image::~Image()
{
}