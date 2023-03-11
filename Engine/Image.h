#pragma once

#include "Transform.h"
#include "Game.h";

class Image : public Component
{
public:
    Image(Entity* owner, const char* key);
    void Update(const float& deltaTime) override;
    void Render() override;
    void Initialize() override {};
    void Start() override;
    void Destroy() override {};
    std::string ToString() override { return m_key; };

private:
    SDL_RendererFlip m_flip;
    Transform* m_transform;
    SDL_Texture* m_texture;
    SDL_Rect m_sourceRect;
    SDL_Rect m_destinationRect;
    const char* m_key;
    float m_angle;
};

