#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

class Shader
{
public:
    // Shader(std::string vertexPath, std::string fragmentPath, std::string shaderName);
    Shader(std::string_view vertexPath, std::string_view fragmentPath, std::string shaderName = "unknown");

    ~Shader();

    void addUniform(const std::string &name);
    void setUniform(std::string_view name, int value);
    void setUniform(std::string_view name, float value);
    void setUniform(std::string_view name, bool value);
    void setUniform(std::string_view name, const glm::mat4 &aMat);
    void setUniform(std::string_view name, const glm::mat3 &aMat);
    void setUniform(std::string_view name, const glm::vec3 &aVec);
    void setUniform(std::string_view name, const glm::vec4 &aVec);
    void use();

private:
    std::unordered_map<std::string, unsigned int> m_UniformCache;

    void cacheUniforms();
    void createProgram();
    void checkCompileErrors(GLenum type, std::string &source);

    GLuint compileShader(GLuint id, GLenum type);

    GLuint m_ProgramID;
    std::string shaderName;
    unsigned int vertexShader;
    unsigned int fragmentShader;
};

#endif