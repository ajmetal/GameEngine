#include "pch.h"

#include "CacheManager.h"

CacheManager::CacheManager()
{ }

bool CacheManager::Initialize()
{
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags)) {
    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    return true;
  }
  LoadImage("default", DEFAULT_IMG_PATH);
  //if (TTF_Init() == -1) {
  //  printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
  //  return true;
  //}
  return false;
}

bool CacheManager::LoadImage(const char * key, const char * filename)
{
  SDL_Surface * loadedSurface = IMG_Load(filename);
  if (nullptr == loadedSurface)
  {
    printf("Unable to load image %s! SDL Error: %s\n", filename, SDL_GetError());
    return true;
  }
  m_surfaces[key] = loadedSurface;
  return false;
}

bool CacheManager::LoadSpriteSheet(const char * key, const char * imageFilename, const char * dataFilename)
{
  if (true == LoadImage(key, imageFilename)) {
    return true;
  }
  if (true == LoadJson(key, dataFilename)) {
    return true;
  }


  return false;
}

//bool Cache::LoadFont(const char * key, const char * filename)
//{
//  TTF_Font * loadedFont = TTF_OpenFont(filename, 28);
//  if (nullptr == loadedFont) {
//    printf("Unable to load font %s! SDL Error: %s\n", filename, SDL_GetError());
//    return true;
//  }
//  m_ttfFonts[key] = loadedFont;
//  return false;
//}

bool CacheManager::LoadBitmapFont(const char* key, const char* bmpFilename, const char* jsonFilename)
{
  // Read whole file into a buffer
  FILE* fp;
  fopen_s(&fp, jsonFilename, "r");
  fseek(fp, 0, SEEK_END);
  size_t filesize = (size_t)ftell(fp);
  fseek(fp, 0, SEEK_SET);
  char* buffer = (char*)malloc(filesize + 1);
  size_t readLength = fread(buffer, 1, filesize, fp);
  buffer[readLength] = '\0';
  fclose(fp);
  // In situ parsing the buffer into fontData, buffer will also be modified
  rapidjson::Document fontData;
  fontData.ParseInsitu(buffer);
  //create the data to hold the bitmapfont rect values
  size_t size = fontData["char_count"].GetInt();
  LetterData* metrics = new LetterData[size];
  memset(metrics, 0, size * sizeof(SDL_Rect));
  for (size_t i = 0; i < size; ++i) {
    char character = fontData["chars"][i].GetInt();
    int index = character - ' ';
    metrics[index] = {
      fontData["advance"][i].GetInt(),
      fontData["offset_x"][i].GetInt(),
      fontData["offset_y"][i].GetInt() * -1,
      fontData["pack_x"][i].GetInt(),
      fontData["pack_y"][i].GetInt(),
      fontData["width"][i].GetInt(),
      fontData["height"][i].GetInt(),
    };
  }
  m_fontData[key] = metrics;
  //load the texture for the bitmapfont
  return LoadImage(key, bmpFilename);
}

bool CacheManager::LoadJson(const char * key, const char * jsonFilename)
{
  // Read whole file into a buffer
  FILE* fp;
  fopen_s(&fp, jsonFilename, "r");
  fseek(fp, 0, SEEK_END);
  size_t filesize = (size_t)ftell(fp);
  fseek(fp, 0, SEEK_SET);
  char* buffer = (char*)malloc(filesize + 1);
  size_t readLength = fread(buffer, 1, filesize, fp);
  buffer[readLength] = '\0';
  fclose(fp);
  // In situ parsing the buffer into fontData, buffer will also be modified
  rapidjson::Document* data = new rapidjson::Document();
  data->ParseInsitu(buffer);
  m_jsonData[key] = data;
  return false;
}

void CacheManager::FormatTexturesToScreen(SDL_Renderer* renderer, SDL_Surface* screen)
{
  for (auto & it : m_surfaces) {
    SDL_Surface * optimizedSurface = SDL_ConvertSurface(it.second, screen->format, 0);
    if (nullptr == optimizedSurface) {
      printf("Unable to optimize surface %s: %s\n", it.first, SDL_GetError());
      continue;
    }
    SDL_FreeSurface(it.second);
    it.second = nullptr;
    it.second = optimizedSurface;
    SDL_Texture* finalTexture = SDL_CreateTextureFromSurface(renderer, optimizedSurface);
    if (finalTexture == NULL)
    {
      printf("Unable to create texture from %s! SDL Error: %s\n", it.first, SDL_GetError());
      continue;
    }
    m_textures[it.first] = finalTexture;
  }
}

SDL_Texture* CacheManager::GetTexture(const char* key)
{
  if (m_textures.find(key) == m_textures.end()) {
    return nullptr;
  }
  return m_textures[key];
}

SDL_Texture* CacheManager::GetBitmapFont(const char * key, LetterData** rectArray)
{
  if (m_textures.find(key) == m_textures.end()) {
    return nullptr;
  }
  *rectArray = m_fontData[key];
  return m_textures[key];
}

rapidjson::Value* CacheManager::GetJson(const char * key)
{
  if (m_jsonData.find(key) == m_jsonData.end()) {
    return nullptr;
  }
  return m_jsonData[key];
}

CacheManager::~CacheManager()
{
  for (auto & it : m_surfaces) {
    SDL_FreeSurface(it.second);
    it.second = nullptr;
  }
  for (auto & it : m_textures) {
    SDL_DestroyTexture(it.second);
    it.second = nullptr;
  }
  //for (auto & it : m_ttfFonts) {
  //  TTF_CloseFont(it.second);
  //  it.second = nullptr;
  //}
  for (auto & it : m_fontData) {
    delete[] it.second;
    it.second = nullptr;
  }
  //TTF_Quit();
  IMG_Quit();
}
