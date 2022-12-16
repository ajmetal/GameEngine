#include "pch.h"
#include "InputManager.h"


void InputManager::Reset()
{
    //for (unsigned i = SDLK_UNKNOWN; i <= SDLK_z; ++i) {
    //    m_keyStates[i] = false;
    //}
}

void InputManager::Initialize()
{
    ////hardcoding here! get all keys
    //for (unsigned i = SDLK_UNKNOWN; i <= SDLK_z; ++i) {
    //    m_keyStates.push_back(false);
    //}
}

void InputManager::Update(const float& deltaTime)
{
    SDL_Event event;
    //memset(m_keyStates, 0, sizeof(m_keyStates));
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            //Quit();
            break;
        case SDL_KEYDOWN: {
            //std::cout << "key down: " << event.key.keysym.sym << std::endl;
            m_keyStates[event.key.keysym.scancode] = true;
            break;
        }
        case SDL_KEYUP: {
            //std::cout << "key up: " << event.key.keysym.sym << std::endl;
            m_keyStates[event.key.keysym.scancode] = false;
            break;
        }
        case SDL_MOUSEMOTION: {
            SDL_GetMouseState(&m_mouseX, &m_mouseY);
            //printf("Mouse Position: x: %i, y: %i", m_mouseX, m_mouseY);
            break;
        }
        case SDL_MOUSEBUTTONDOWN: {
            SDL_MouseButtonEvent buttonEvent = event.button;
            if (buttonEvent.button == SDL_BUTTON_LEFT) {
                m_mouseLeftDown = true;
            }
            //m_keyStates[event.button.] = true;
            break;
        }
        case SDL_MOUSEBUTTONUP: {
            auto button = event.button;
            if (button.button == SDL_BUTTON_LEFT) {
                m_mouseLeftDown = false;
            }
            break;
        }
        }
    }
}

bool InputManager::GetKeyState(const int& keyCode)
{
    return m_keyStates[keyCode];
}

InputManager::InputManager()
    : m_mouseX(0)
    , m_mouseY(0)
{
}


InputManager::~InputManager()
{
}
