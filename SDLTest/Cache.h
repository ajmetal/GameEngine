#pragma once

#include <unordered_map>

#include <SDL.h>
#include <SDL_image.h>
//#include <SDL_ttf.h>

#include <rapidjson/document.h>
#include <rapidjson/reader.h>

struct LetterData {
  int advance;
  int offset_x;
  int offset_y;
  int pack_x;
  int pack_y;
  int width;
  int height;
};

class Cache
{
public:
  Cache();
  bool Initialize();
  bool LoadImage(const char* key, const char* filename);
  bool LoadFont(const char* key, const char* filename);
  bool LoadBitmapFont(const char* key, const char* bmpFilename, const char* jsonFilename);
  void FormatTexturesToScreen(SDL_Renderer* renderer, SDL_Surface* screen);
  SDL_Texture* GetTexture(const char* key);
  SDL_Texture* GetBitmapFont(const char* key, LetterData** rectArray);
  ~Cache();
protected:
private:
  const char * DEFAULT_IMG_PATH = "assets/img/default.png";
  std::unordered_map<const char*, SDL_Surface*> m_surfaces;
  std::unordered_map<const char*, SDL_Texture*> m_textures;
  std::unordered_map<const char*, LetterData*> m_fontData;
};

