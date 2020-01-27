#pragma once

#include "SDL.h"
#include <vector>
#include <iostream>

class InputManager
{
private:
  void Reset();
  std::vector<bool> m_keyStates;

public:

  void Initialize();
  void Update(const float& deltaTime);

  bool GetKeyState(const int& keyCode);

  InputManager();
  ~InputManager();
};

