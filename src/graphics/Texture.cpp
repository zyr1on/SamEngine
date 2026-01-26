#include "Texture.h"
#include <stb_image.h>
#include <iostream>

Texture::Texture(const std::string& path, GLenum type)
    : id(0), type(type), path(path), width(0), height(0), nrChannels(0)
{
    glGenTextures(1, &id);
    glBindTexture(type, id);

    // Default parametreler
    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format;
        if (nrChannels == 1) format = GL_RED;
        else if (nrChannels == 3) format = GL_RGB;
        else if (nrChannels == 4) format = GL_RGBA;
        else format = GL_RGB;

        glTexImage2D(type, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(type);
    } else {
        std::cerr << "Failed to load texture: " << path << std::endl;
    }
    stbi_image_free(data);

    glBindTexture(type, 0);
}

void Texture::bind(int unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(type, id);
}

void Texture::unbind() const {
    glBindTexture(type, 0);
}

void Texture::setWrap(GLenum s, GLenum t) {
    glBindTexture(type, id);
    glTexParameteri(type, GL_TEXTURE_WRAP_S, s);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, t);
    glBindTexture(type, 0);
}

void Texture::setFilter(GLenum minFilter, GLenum magFilter) {
    glBindTexture(type, id);
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, magFilter);
    glBindTexture(type, 0);
}

Texture::~Texture() {
    glDeleteTextures(1, &id);
}
