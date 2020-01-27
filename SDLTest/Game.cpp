#include "pch.h"

#include "Game.h"

using namespace std::chrono;
using namespace std::chrono_literals;

SDL_Renderer* Game::s_renderer;
CacheManager Game::s_cacheManager;
InputManager Game::s_inputManager;

Game::Game(const int& width, const int& height)
  : m_width(width)
  , m_height(height)
  , m_window(nullptr)
  , m_screen(nullptr)
  , m_entityManager()
  , m_quitting(false)
  , m_scaleFactor(0)
  , m_lastTime(0)
  , m_msPerFrame(1000 / FRAMERATE)
{ }

bool Game::Initialize()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    return true;
  }
  m_window = SDL_CreateWindow(
    "Hello, World!",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    m_width,
    m_height,
    SDL_WINDOW_ALLOW_HIGHDPI
  );
  s_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawColor(s_renderer, 0x00, 0x00, 0x00, 0x00);
  if (nullptr == m_window) {
    printf("Could not create SDL Window: %s\n", SDL_GetError());
    return true;
  }
  m_screen = SDL_GetWindowSurface(m_window);
  if (nullptr == m_screen) {
    printf("Could not get window surface: %s\n", SDL_GetError());
    return true;
  }

  s_cacheManager = CacheManager();
  s_cacheManager.Initialize();

  return false;
}

bool Game::Update()
{
  if (m_quitting) {
    return true;
  };

  while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_lastTime + m_msPerFrame)) {
    //wait if we're above our target framerate
  }

  float now = SDL_GetTicks();

  float deltaTime = (now - m_lastTime) / 1000.0f;
  //clamp deltaTime to a max in case we were debugging
  deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;
  m_lastTime = now;

  s_inputManager.Update(deltaTime);

  if (false == m_entityManager.HasNoEntities()) {
    m_entityManager.Update(deltaTime);
  }
  
  Render();
  return false;
}

void Game::Quit()
{
  m_quitting = true;
}

bool Game::Render()
{
  SDL_SetRenderDrawColor(s_renderer, 0, 0, 0, 255);
  SDL_RenderClear(s_renderer);
  if (m_entityManager.HasNoEntities()) {
    return false;
  }
  m_entityManager.Render();
  SDL_RenderPresent(s_renderer);
  return false;
}

void Game::Rescale(const int& scaleFactor)
{
  m_scaleFactor = scaleFactor;
}

Entity& Game::AddEntity(const char* name, const float& worldX, const float& worldY)
{
    //if (e->Initialize() == false) {
    //  m_activeObjects.push_back(obj);
    //  obj->SetPosition(worldX, worldY);
    //}
  return m_entityManager.AddEntity(name);
}

void Game::ListAllEntities()
{
  m_entityManager.ListAllEntities();
}

void Game::ListAllComponents()
{
  m_entityManager.ListAllComponents();
}

void Game::LoadImage(const char * key, const char * filename)
{
  s_cacheManager.LoadImage(key, filename);
}

void Game::StartScene()
{
  m_entityManager.StartScene();
  s_inputManager.Initialize();
}

Game::~Game()
{
  SDL_DestroyRenderer(s_renderer);
  s_renderer = nullptr;
  SDL_DestroyWindow(m_window);
  m_window = nullptr;
  SDL_Quit();
}
