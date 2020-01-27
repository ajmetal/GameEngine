#pragma once

#include <iostream>
#include <vector>
#include <chrono>

#include <SDL.h>

//#include "GameObject.h"
#include "Entity.h"
#include "EntityManager.h"
#include "CacheManager.h"
#include "InputManager.h"

const int FRAMERATE = 60;

class Game {
public:
  Game(const int& width, const int& height);
  bool Initialize();
  bool Update();
  void Quit();
  void Rescale(const int& scaleFactor);
  Entity& AddEntity(const char* name, const float& worldX = 0, const float& worldY = 0);
  void ListAllEntities();
  void ListAllComponents();
  void LoadImage(const char* key, const char* filename);
  SDL_Surface * GetScreen() {
    return m_screen;
  }

  void StartScene();

  ~Game();

  struct {
    bool rightDown;
    bool leftDown;
    bool upDown;
    bool downDown;

    void reset() {
      memset(this, 0, sizeof(this));
    }
  } Input;

  static SDL_Renderer* s_renderer;
  static CacheManager s_cacheManager;
  static InputManager s_inputManager;

protected:

private:
  bool ProcessInput();
  bool Render();
  EntityManager m_entityManager;
  SDL_Surface * m_screen;
  SDL_Window * m_window;
  int m_lastTime;
  int m_msPerFrame;
  int m_scaleFactor;
  int m_width;
  int m_height;
  bool m_quitting;

};
