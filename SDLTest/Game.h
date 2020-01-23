#pragma once

#include <iostream>
#include <vector>
#include <chrono>

#include <SDL.h>

#include "GameObject.h"

const int FRAMERATE = 60;

class Game {
public:
  Game(const int& width, const int& height);
  bool Initialize();
  bool Update();
  void Quit();
  void Rescale(const int& scaleFactor);
  void AddObject(GameObject * obj, const float& worldX = 0, const float& worldY = 0);
  ~Game();
  SDL_Surface * GetScreen() {
    return m_screen;
  }
  SDL_Renderer* GetRenderer() {
    return m_renderer;
  }

  struct {
    bool rightDown;
    bool leftDown;
    bool upDown;
    bool downDown;

    void reset() {
      memset(this, 0, sizeof(this));
    }
  } Input;

protected:

private:
  bool Render();
  bool ProcessInput();

  std::vector<GameObject*> m_activeObjects;
  std::vector<GameObject*> m_inactiveObjects;
  //std::chrono::time_point<std::chrono::high_resolution_clock> m_previous;
  Uint32 m_lastTime;
  float m_lag;
  Uint32 m_msPerFrame;
  //std::vector<Camera*> m_cameras;
  //Camera* m_activeCamera;
  SDL_Surface * m_screen;
  SDL_Window * m_window;
  SDL_Renderer* m_renderer;
  int m_scaleFactor;
  int m_width;
  int m_height;
  bool m_quitting;

};
