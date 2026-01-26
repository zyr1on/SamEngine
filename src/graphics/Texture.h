#pragma once
#include <string>
#include <glad/glad.h>

class Texture {
public:
    GLuint id;
    GLenum type;
    std::string path;
    int width, height, nrChannels;

    Texture(const std::string& path, GLenum type = GL_TEXTURE_2D);

    void bind(int unit = 0) const;
    void unbind() const;

    void setWrap(GLenum s, GLenum t);
    void setFilter(GLenum minFilter, GLenum magFilter);

    ~Texture();
};
