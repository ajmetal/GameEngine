#pragma once
#include "pch.h"

#include <string>

#include "Component.h"

class Text : public Component
{
public:
    Text(const char* fontKey, const char* textString = "", SDL_Color color = {255,255,255,1});
    ~Text() {};
    virtual void Initialize() override;
    virtual void Update(const float& deltaTime) override;
    virtual void Render() override;
    virtual void Destroy() override;
    virtual std::string ToString() override;
    void SetString(const char *);

private:
    const char* m_key;
    TTF_Font* m_ttfFont;
    std::string m_textString;
    SDL_Color m_color;
};

