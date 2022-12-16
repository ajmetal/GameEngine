#pragma once

#include "SDL.h"
#include <vector>
#include <iostream>

class InputManager
{
private:
    void Reset();
    bool m_keyStates[SDL_NUM_SCANCODES];
    int m_mouseX;
    int m_mouseY;
    bool m_mouseLeftDown;

public:

    void Initialize();
    void Update(const float& deltaTime);

    bool GetKeyState(const int& keyCode);
    inline int GetMouseX() { return m_mouseX; };
    inline int GetMouseY() { return m_mouseY; };
    inline bool GetMouseLeftDown() { return m_mouseLeftDown; };
    InputManager();
    ~InputManager();
};

