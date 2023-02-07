#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <array>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

class LTexture
{
  public:
    LTexture();
    LTexture(std::string path_folder);
    ~LTexture();
    bool loadTextures(SDL_Renderer *renderer);
    SDL_Texture *getTexture(std::string key);
    std::map<std::string, SDL_Texture *> &getTextureMap() { return m_textureMap; }

  private:
    std::string buildKey(std::string path);
    std::string m_path_folder;
    std::map<std::string, SDL_Texture *> m_textureMap;
};
