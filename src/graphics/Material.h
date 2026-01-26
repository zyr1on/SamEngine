#ifndef MATERIAL_H
#define MATERIAL_H

#include "Shader.h"
#include <memory>
#include <unordered_map>
#include <variant>

class Material {
public:
    using UniformValue = std::variant<int, float, glm::vec3, glm::vec4, glm::mat4>;

    Material(std::shared_ptr<Shader> shader);

    void SetInt(const std::string& name, int value);
    void SetFloat(const std::string& name, float value);
    void SetVec3(const std::string& name, const glm::vec3& value);
    void SetVec4(const std::string& name, const glm::vec4& value);
    void SetMat4(const std::string& name, const glm::mat4& value);
    void SetTexture(const std::string& name, unsigned int textureID, int slot);
    void SetVec3Array(const std::string& name, const std::vector<glm::vec3>& values);

    
    void Apply() const;
    std::shared_ptr<Shader> GetShader() const { return shader; }

private:
    std::shared_ptr<Shader> shader;
    std::unordered_map<std::string, UniformValue> uniforms;
    std::unordered_map<std::string, std::pair<unsigned int, int>> textures; // textureID, slot

    void ApplyUniform(const std::string& name, const UniformValue& value) const;
};

#endif