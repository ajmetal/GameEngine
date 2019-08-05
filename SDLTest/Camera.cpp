#include "pch.h"
#include "Camera.h"

Camera::Camera(Game & game, int x, int y, int w, int h)
  : m_game(game)
  , m_viewport({x, y, w, h})
{ }

bool Camera::Initialize()
{
  return false;
}

bool Camera::Render(SDL_Renderer * renderer)
{
  //was there an error?
  if (0 != SDL_RenderSetViewport(renderer, &m_viewport)) {
    printf("Error setting viewport of camera: %s", SDL_GetError());
    return true;
  }

  return false;
}

void Camera::Update(float deltaTime)
{

}

Camera::~Camera()
{
  //delete m_viewport;
  //m_viewport = nullptr;
}
