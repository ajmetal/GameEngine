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

static SDL_Surface* s_screen;
static SDL_Renderer* s_renderer;
static CacheManager s_cacheManager;
static InputManager s_inputManager;
static SDL_Window* s_window;

bool Initialize();
bool Update();
void Quit();
void Rescale(const int& scaleFactor);
Entity& AddEntity(const char* name, const float& worldX = 0, const float& worldY = 0);
void ListAllEntities();
void ListAllComponents();
void LoadImage(const char* key, const char* filename);
void StartScene();


bool ProcessInput();
bool Render();
