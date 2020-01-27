#include "pch.h"
#include "InputManager.h"


void InputManager::Reset()
{
  for (unsigned i = SDLK_UNKNOWN; i <= SDLK_z; ++i) {
    m_keyStates[i] = false;
  }
}

void InputManager::Initialize()
{
  //hardcoding here! get all keys
  for (unsigned i = SDLK_UNKNOWN; i <= SDLK_z; ++i) {
    m_keyStates.push_back(false);
  }
}

void InputManager::Update(const float& deltaTime)
{
  SDL_Event event;
  //Reset();
  //event loop
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        //Quit();
        break;
      case SDL_KEYDOWN: {
        //std::cout << "key down: " << event.key.keysym.sym << std::endl;
        m_keyStates[event.key.keysym.sym] = true;
      }
      break;
      case SDL_KEYUP: {
        //std::cout << "key up: " << event.key.keysym.sym << std::endl;
        m_keyStates[event.key.keysym.sym] = false;
      }
    }
  }
}

bool InputManager::GetKeyState(const int & keyCode)
{
  return m_keyStates[keyCode];
}

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}
