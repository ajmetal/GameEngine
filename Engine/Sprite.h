#pragma once

#include "Transform.h";
#include "Game.h";

class Sprite : public Component
{
public:
    Sprite(Entity* owner);
    Sprite(Entity* owner, const char* key, const bool& isFixed = false);

    //Sprite(Sprite&);
    //Sprite(Sprite&&);
    //void operator=(Sprite&);
    //void operator=(Sprite&&);
    ~Sprite();

    SDL_RendererFlip m_flip;
    //Sprite* AddAnimation(const char* key, const int& numFrames, const int& animationSpeed);
    void Play(const std::string& key);

    //void SetTexture(const char* key);
    void Update(const float& deltaTime) override;
    void Render() override;
    void Initialize() override;
    void Start() override;
    void Destroy() override;
    std::string ToString() override;
    //void OnEnable() override {};
    //void OnDisable() override {};

private:
    struct Animation {
        std::string m_key;
        unsigned int m_currentFrame = 0;
        unsigned int m_numFrames = 0;
        unsigned int m_animationSpeed = 1;
        std::vector<SDL_Rect*> m_frames;
    };

    Transform* m_transform;
    SDL_Texture* m_texture;
    SDL_Rect m_sourceRect;
    SDL_Rect m_destinationRect;
    const char* m_key;
    bool m_isAnimating;
    std::unordered_map<std::string, Animation*> m_animations;
    Animation* m_currentAnimation;

};

