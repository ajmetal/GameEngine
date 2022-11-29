#include "pch.h"

#include "Game.h"

using namespace std::chrono;
using namespace std::chrono_literals;

Game* Game::s_instance = nullptr;

/******************************************************************************
******************************************************************************/
Game::Game()
    : m_renderer(nullptr)
    , m_screen(nullptr)
    , m_window(nullptr)
    , m_lastTime(0)
    , m_msPerFrame(0)
    , m_scaleFactor(0)
    , m_width(0)
    , m_height(0)
    , m_quitting(false)
{}

/******************************************************************************
******************************************************************************/
Game::~Game()
{
    //for (auto& it : m_surfaces) {
    //    SDL_FreeSurface(it.second);
    //    it.second = nullptr;
    //}
    for (auto& it : m_textures) {
        SDL_DestroyTexture(it.second);
        it.second = nullptr;
    }
    for (auto& it : m_ttfFonts) {
        TTF_CloseFont(it.second);
        it.second = nullptr;
    }
    //for (auto& it : m_fontData) {
    //    delete[] it.second;
    //    it.second = nullptr;
    //}
    TTF_Quit();
    IMG_Quit();
    delete s_instance;
}

/******************************************************************************
******************************************************************************/
Game& Game::GetInstance()
{
    if (s_instance == nullptr) {
        s_instance = new Game();
    }
    return *s_instance;
}

/******************************************************************************
******************************************************************************/
bool Game::LoadImage(const char* key, const char* filename)
{
    SDL_Surface* loadedSurface = IMG_Load(filename);
    if (nullptr == loadedSurface)
    {
        printf("Unable to load image %s! SDL Error: %s\n", filename, SDL_GetError());
        return false;
    }
    SDL_Surface* optimizedSurface = SDL_ConvertSurface(loadedSurface, m_screen->format, 0);
    if (nullptr == optimizedSurface) {
        printf("Unable to optimize surface %s: %s\n", key, SDL_GetError());
        return false;
    }
    SDL_FreeSurface(loadedSurface);
    loadedSurface = nullptr;
    SDL_Texture* finalTexture = SDL_CreateTextureFromSurface(m_renderer, optimizedSurface);
    if (finalTexture == NULL)
    {
        printf("Unable to create texture from %s! SDL Error: %s\n", key, SDL_GetError());
        return false;
    }
    m_textures[key] = finalTexture;
    return true;
}

/******************************************************************************
******************************************************************************/
bool Game::LoadSpriteSheet(const char* key, const char* imageFilename, const char* dataFilename)
{
    if (!LoadImage(key, imageFilename)) {
        return false;
    }
    if (!LoadJson(key, dataFilename)) {
        return false;
    }
    return true;
}

/******************************************************************************
******************************************************************************/
bool Game::LoadFont(const char* key, const char* filename)
{
    TTF_Font* loadedFont = TTF_OpenFont(filename, 24);
    if (nullptr == loadedFont) {
        printf("Unable to load font %s! SDL Error: %s\n", filename, SDL_GetError());
        return true;
    }
    m_ttfFonts[key] = loadedFont;
    return false;
}

///******************************************************************************
//******************************************************************************/
//bool Game::LoadBitmapFont(const char* key, const char* bmpFilename, const char* jsonFilename)
//{
//    // Read whole file into a buffer
//    FILE* fp;
//    fopen_s(&fp, jsonFilename, "r");
//    if (fp == NULL) {
//        printf("unable to open file: %s", jsonFilename);
//        return false;
//    }
//    fseek(fp, 0, SEEK_END);
//    size_t filesize = (size_t)ftell(fp);
//    fseek(fp, 0, SEEK_SET);
//    char* buffer = (char*)malloc(filesize + 1);
//    if (buffer == nullptr) {
//        printf("Couldnt allocate memory for %s", jsonFilename);
//        return false;
//    }
//    size_t readLength = fread(buffer, 1, filesize, fp);
//    buffer[readLength] = '\0';
//    fclose(fp);
//    // In situ parsing the buffer into fontData, buffer will also be modified
//    rapidjson::Document fontData;
//    fontData.ParseInsitu(buffer);
//    //create the data to hold the bitmapfont rect values
//    size_t size = fontData["char_count"].GetInt();
//    LetterData* metrics = new LetterData[size];
//    memset(metrics, 0, size * sizeof(SDL_Rect));
//    for (size_t i = 0; i < size; ++i) {
//        char character = fontData["chars"][i].GetInt();
//        int index = character - ' ';
//        metrics[index] = {
//          fontData["advance"][i].GetInt(),
//          fontData["offset_x"][i].GetInt(),
//          fontData["offset_y"][i].GetInt() * -1,
//          fontData["pack_x"][i].GetInt(),
//          fontData["pack_y"][i].GetInt(),
//          fontData["width"][i].GetInt(),
//          fontData["height"][i].GetInt(),
//        };
//    }
//    m_fontData[key] = metrics;
//    //load the texture for the bitmapfont
//    return LoadImage(key, bmpFilename);
//}

/******************************************************************************
******************************************************************************/
bool Game::LoadJson(const char* key, const char* jsonFilename)
{
    // Read whole file into a buffer
    FILE* fp;
    fopen_s(&fp, jsonFilename, "r");
    if (fp == NULL) {
        printf("Error loading json file: %s\n", jsonFilename);
        return false;
    }
    fseek(fp, 0, SEEK_END);
    size_t filesize = (size_t)ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char* buffer = (char*)malloc(filesize + 1);
    if (buffer == NULL) {
        printf("Unable to allocate memory for: %s\n", jsonFilename);
        return false;
    }
    size_t readLength = fread(buffer, 1, filesize, fp);
    buffer[readLength] = '\0';
    fclose(fp);
    // In situ parsing the buffer into fontData, buffer will also be modified
    rapidjson::Document* data = new rapidjson::Document();
    data->ParseInsitu(buffer);
    m_jsonData[key] = data;
    return true;
}

/******************************************************************************
******************************************************************************/
SDL_Texture* Game::GetTexture(const char* key)
{
    if (m_textures.find(key) == m_textures.end()) {
        return nullptr;
    }
    return m_textures[key];
}

///******************************************************************************
//******************************************************************************/
//SDL_Texture* Game::GetBitmapFont(const char* key, LetterData** rectArray)
//{
//    if (m_textures.find(key) == m_textures.end()) {
//        return nullptr;
//    }
//    *rectArray = m_fontData[key];
//    return m_textures[key];
//}

/******************************************************************************
******************************************************************************/
rapidjson::Value* Game::GetJson(const char* key)
{
    if (m_jsonData.find(key) == m_jsonData.end()) {
        return nullptr;
    }
    return m_jsonData[key];
}

/******************************************************************************
******************************************************************************/
TTF_Font* Game::GetFont(const char* key)
{
    if (m_ttfFonts.find(key) == m_ttfFonts.end()) {
        return nullptr;
    }
    return m_ttfFonts[key];
}

/******************************************************************************
******************************************************************************/
bool Game::Initialize(const float& msPerFrame, const int& scaleFactor, const int& width, const int& height)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return true;
    }
    m_msPerFrame = msPerFrame;
    m_scaleFactor = scaleFactor;
    m_width = width;
    m_height = height;

    m_window = SDL_CreateWindow(
        "Game",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        m_width,
        m_height,
        SDL_WINDOW_ALLOW_HIGHDPI
    );
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0x00);
    if (nullptr == m_window) {
        printf("Could not create SDL Window: %s\n", SDL_GetError());
        return true;
    }
    m_screen = SDL_GetWindowSurface(m_window);
    if (nullptr == m_screen) {
        printf("Could not get window surface: %s\n", SDL_GetError());
        return true;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }
    LoadImage("default", DEFAULT_IMG_PATH);
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }
    LoadFont("arial", DEFAULT_TTF_PATH);

    return false;
}

/******************************************************************************
******************************************************************************/
void Game::StartScene()
{
    m_inputManager.Initialize();
    m_entityManager.Initialize();
}

/******************************************************************************
******************************************************************************/
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

    m_inputManager.Update(deltaTime);

    //if (!s_entityManager.HasNoEntities()) {
    m_entityManager.Update(deltaTime);
    //}

    Render();
    return false;
}

/******************************************************************************
******************************************************************************/
void Game::Quit()
{
    m_quitting = true;
}

/******************************************************************************
******************************************************************************/
bool  Game::Render()
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
    if (m_entityManager.HasNoEntities()) {
        return false;
    }
    m_entityManager.Render();
    SDL_RenderPresent(m_renderer);
    return false;
}

/******************************************************************************
******************************************************************************/
void Game::Rescale(const int& scaleFactor)
{
    m_scaleFactor = scaleFactor;
}

/******************************************************************************
******************************************************************************/
Entity* Game::AddEntity(const char* name, const float& worldX, const float& worldY)
{
    //if (e->Initialize() == false) {
    //  s_activeObjects.push_back(obj);
    //  obj->SetPosition(worldX, worldY);
    //}
    return m_entityManager.AddEntity(name);
}

/******************************************************************************
******************************************************************************/
void Game::ListAllEntities()
{
    m_entityManager.ListAllEntities();
}

/******************************************************************************
******************************************************************************/
void  Game::ListAllComponents()
{
    m_entityManager.ListAllComponents();
}

///******************************************************************************
//******************************************************************************/
//void  Game::StartScene()
//{
//    s_entityManager.StartScene();
//    s_inputManager.Initialize();
//}
