#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <glad/glad.h>
#include <string>
#include <unordered_map> // Değişti

class TextureManager {
public:
    static TextureManager& getInstance() {
        static TextureManager instance;
        return instance;
    }

    unsigned int loadTexture(const std::string& path);
    void clear();

private:
    TextureManager() {}
    ~TextureManager() { clear(); }

    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;
    
    std::unordered_map<std::string, unsigned int> m_textures;
};

#endif