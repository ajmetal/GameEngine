#pragma once

#include "SDL.h"
#include <vector>
#include <iostream>

class InputManager
{
private:
    void Reset();
    //SDLK_AUDIOFASTFORWARD happens to be the last enum for SDL keys
    bool m_keyStates[SDL_NUM_SCANCODES];
    int m_mouseX;
    int m_mouseY;

public:

    void Initialize();
    void Update(const float& deltaTime);

    bool GetKeyState(const int& keyCode);
    inline int GetMouseX() { return m_mouseX; };
    inline int GetMouseY() { return m_mouseY; };
    InputManager();
    ~InputManager();
};

