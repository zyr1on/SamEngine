#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void Use() const;
    unsigned int GetProgramID() const { return programID; }

    // Uniform setters - location'ları cache'ler
    void SetInt(const std::string& name, int value);
    void SetFloat(const std::string& name, float value);
    void SetVec3(const std::string& name, const glm::vec3& value);
    void SetVec4(const std::string& name, const glm::vec4& value);
    void SetMat4(const std::string& name, const glm::mat4& value);
    void SetVec3Array(const std::string& name, const std::vector<glm::vec3>& values);

private:
    unsigned int programID;
    mutable std::unordered_map<std::string, int> uniformLocationCache;

    int GetUniformLocation(const std::string& name) const;
    std::string ReadFile(const std::string& path);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    void LinkProgram(unsigned int vertexShader, unsigned int fragmentShader);
};

#endif