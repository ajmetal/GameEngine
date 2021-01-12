#include "pch.h"

#include "Game.h"

using namespace std::chrono;
using namespace std::chrono_literals;

extern SDL_Surface* s_screen;
extern SDL_Window* s_window;

static EntityManager s_entityManager;
static int s_lastTime;
static int s_msPerFrame;
static int s_scaleFactor;
static int s_width;
static int s_height;
static bool s_quitting;

static SDL_Renderer* s_renderer;
static CacheManager s_cacheManager;
static InputManager s_inputManager;

struct {
    bool rightDown;
    bool leftDown;
    bool upDown;
    bool downDown;

    void reset() {
        memset(this, 0, sizeof(this));
    }
} Input;

bool Initialize()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return true;
    }
    s_window = SDL_CreateWindow(
        "Hello, World!",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        s_width,
        s_height,
        SDL_WINDOW_ALLOW_HIGHDPI
    );
    s_renderer = SDL_CreateRenderer(s_window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(s_renderer, 0x00, 0x00, 0x00, 0x00);
    if (nullptr == s_window) {
        printf("Could not create SDL Window: %s\n", SDL_GetError());
        return true;
    }
    s_screen = SDL_GetWindowSurface(s_window);
    if (nullptr == s_screen) {
        printf("Could not get window surface: %s\n", SDL_GetError());
        return true;
    }

    s_cacheManager = CacheManager();
    s_cacheManager.Initialize();

    return false;
}

bool Update()
{
    if (s_quitting) {
        return true;
    };

    while (!SDL_TICKS_PASSED(SDL_GetTicks(), s_lastTime + s_msPerFrame)) {
        //wait if we're above our target framerate
    }

    float now = SDL_GetTicks();

    float deltaTime = (now - s_lastTime) / 1000.0f;
    //clamp deltaTime to a max in case we were debugging
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;
    s_lastTime = now;

    s_inputManager.Update(deltaTime);

    if (false == s_entityManager.HasNoEntities()) {
        s_entityManager.Update(deltaTime);
    }

    Render();
    return false;
}

void Quit()
{
    s_quitting = true;
}

bool Render()
{
    SDL_SetRenderDrawColor(s_renderer, 0, 0, 0, 255);
    SDL_RenderClear(s_renderer);
    if (s_entityManager.HasNoEntities()) {
        return false;
    }
    s_entityManager.Render();
    SDL_RenderPresent(s_renderer);
    return false;
}

void Rescale(const int& scaleFactor)
{
    s_scaleFactor = scaleFactor;
}

Entity& AddEntity(const char* name, const float& worldX, const float& worldY)
{
    //if (e->Initialize() == false) {
    //  s_activeObjects.push_back(obj);
    //  obj->SetPosition(worldX, worldY);
    //}
    return s_entityManager.AddEntity(name);
}

void ListAllEntities()
{
    s_entityManager.ListAllEntities();
}

void ListAllComponents()
{
    s_entityManager.ListAllComponents();
}

void LoadImage(const char* key, const char* filename)
{
    s_cacheManager.LoadImage(key, filename);
}

void StartScene()
{
    s_entityManager.StartScene();
    s_inputManager.Initialize();
}
