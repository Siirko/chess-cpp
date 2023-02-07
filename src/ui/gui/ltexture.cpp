#include "../../../includes/ui/gui/ltexture.hpp"
#include <experimental/filesystem>

LTexture::LTexture() : m_path_folder{""} { m_textureMap = std::map<std::string, SDL_Texture *>(); }

LTexture::LTexture(std::string path_folder) : m_path_folder{path_folder}
{
    m_textureMap = std::map<std::string, SDL_Texture *>();
}

LTexture::~LTexture() {}

std::string LTexture::buildKey(std::string path)
{
    std::string key;
    // remove the extension of the file
    key = path.substr(0, path.find_last_of("."));
    // find _ and divide the string
    key = key.substr(key.find_last_of("/") + 1, key.size());
    std::cout << "Key: " << key << std::endl;
    return key;
}

bool LTexture::loadTextures(SDL_Renderer *renderer)
{
    // iterate over the folder and load all the textures
    // C++11
    std::experimental::filesystem::path path(m_path_folder);
    for (auto &p : std::experimental::filesystem::directory_iterator(path))
    {
        std::string path = p.path().string();
        std::string key = buildKey(path);
        SDL_Surface *surface = IMG_Load(path.c_str());
        if (surface == NULL)
        {
            std::cout << "Error loading surface" << std::endl;
            return false;
        }
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == NULL)
        {
            std::cout << "Error creating texture" << std::endl;
            return false;
        }
        std::cout << "Loading texture: " << key << std::endl;
        this->m_textureMap.insert(std::pair<std::string, SDL_Texture *>(key, texture));
        SDL_FreeSurface(surface);
    }
    return true;
}

SDL_Texture *LTexture::getTexture(std::string key) { return this->m_textureMap[key]; }