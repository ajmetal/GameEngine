#pragma once

#include <SDL.h>
#include "Transform.h";
#include "Game.h";
#include "Animation.h";

class Sprite : public Component
{
private:
  Transform m_transform;
  SDL_Texture * m_texture;
  SDL_Rect m_sourceRect;
  SDL_Rect m_destinationRect;
  const char * m_key;
  bool m_isFixed;
  bool m_isAnimated;
  std::unordered_map<const char*, Animation*> m_animations;
  Animation* m_currentAnimation;

public:
  Sprite(const char* key, const bool& isFixed=false);

  SDL_RendererFlip m_flip;
  Animation& AddAnimation(const char* key, const int& numFrames, const int& animationSpeed);
  void Play(const char* key);

  //void SetTexture(const char* key);
  void Update(const float& deltaTime) override;
  void Render() override;
  void Initialize() override;
  void Destroy() override;
  std::string ToString() override;

  ~Sprite();
};

