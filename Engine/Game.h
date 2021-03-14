#pragma once

#include <iostream>
#include <vector>
#include <chrono>

#include "Entity.h"
#include "EntityManager.h"
#include "InputManager.h"

class Game {
public:
    static Game& GetInstance();
    Game(Game&) = delete;
    void operator=(const Game&) = delete;

    SDL_Surface* m_screen;
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    InputManager m_inputManager;
    EntityManager m_entityManager;

    bool Initialize(
        const float& msPerFrame,
        const int& scaleFactor, 
        const int& width, 
        const int& height);
    bool Update();
    void Quit();
    void Rescale(const int& scaleFactor);
    Entity* AddEntity(const char* name, const float& worldX = 0, const float& worldY = 0);
    void ListAllEntities();
    void ListAllComponents();
    void StartScene();
    bool LoadImage(const char* key, const char* filename);
    bool LoadSpriteSheet(const char* key, const char* imageFilename, const char* jsonFilename);
    bool LoadFont(const char* key, const char* filename);
    //bool LoadBitmapFont(const char* key, const char* bmpFilename, const char* jsonFilename);
    bool LoadJson(const char* key, const char* jsonFilename);
    //void FormatTexturesToScreen(SDL_Renderer* renderer, SDL_Surface* screen);
    SDL_Texture* GetTexture(const char* key);
    //SDL_Texture* GetBitmapFont(const char* key, LetterData** rectArray);
    rapidjson::Value* GetJson(const char* key);
    TTF_Font* GetFont(const char* key);

    //bool ProcessInput();
    bool Render();
private:
    static Game* s_instance;
    Game();
    ~Game();
    int  m_lastTime;
    float  m_msPerFrame;
    int  m_scaleFactor;
    int  m_width;
    int  m_height;
    bool m_quitting;
    const char* DEFAULT_IMG_PATH = "./assets/images/default.png";
    const char* DEFAULT_TTF_PATH = "./assets/fonts/arial.ttf";
    //std::unordered_map<const char*, SDL_Surface*> m_surfaces;
    std::unordered_map<const char*, SDL_Texture*> m_textures;
    //std::unordered_map<const char*, LetterData*> m_fontData;
    std::unordered_map<const char*, rapidjson::Value*> m_jsonData;
    //std::unordered_map<const char*, LetterData*> m_spriteSheetData;
    std::unordered_map<const char*, TTF_Font*> m_ttfFonts;
};