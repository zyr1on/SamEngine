#define STB_IMAGE_IMPLEMENTATION
#include "graphics/TextureManager.h"
#include "third_party/stb_image.h" // stb_image.h
#include <iostream>

unsigned int TextureManager::loadTexture(const std::string& path) {
    
    if (m_textures.find(path) != m_textures.end()) {
        return m_textures[path];
    }

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    
    stbi_set_flip_vertically_on_load(true); 
    
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
    
    if (data) {
        GLenum format;
        if (nrComponents == 1) format = GL_RED;
        else if (nrComponents == 3) format = GL_RGB;
        else if (nrComponents == 4) format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
        
        
        m_textures[path] = textureID;
        std::cout << "[TextureManager::loadTexture] Texture loaded: " << path << std::endl;
    } else {
        std::cout << "[TextureManager::loadTexture] Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

void TextureManager::clear() {
    for (auto const& [path, id] : m_textures) {
        glDeleteTextures(1, &id);
    }
    m_textures.clear();
}