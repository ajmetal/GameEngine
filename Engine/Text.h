#pragma once
#include "pch.h"

#include <string>
#include <SDL_ttf.h>

#include "Component.h"
#include "Vector2.h"

class Text : public Component
{
public:
    Text(Entity* owner, const char* fontKey, const char* textString = "", SDL_Color color = {255,255,255,255});
    ~Text() {};
    virtual void Initialize() override;
    void Start() override {};
    virtual void Update(const float& deltaTime) override;
    virtual void Render() override;
    virtual void Destroy() override;
    virtual std::string ToString() override;
    void SetString(const char *);
    void SetOffset(float x, float y);

private:
    const char* m_key;
    TTF_Font* m_ttfFont;
    std::string m_textString;
    SDL_Color m_color;
    SDL_Rect m_rect;
    SDL_Texture* m_texture;
    Vector2 m_offset;
};

