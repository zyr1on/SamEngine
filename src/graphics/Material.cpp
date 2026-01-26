#include "Material.h"

Material::Material(std::shared_ptr<Shader> shader) : shader(shader) {}

void Material::SetInt(const std::string& name, int value) {
    uniforms[name] = value;
}

void Material::SetFloat(const std::string& name, float value) {
    uniforms[name] = value;
}

void Material::SetVec3(const std::string& name, const glm::vec3& value) {
    uniforms[name] = value;
}

void Material::SetVec4(const std::string& name, const glm::vec4& value) {
    uniforms[name] = value;
}

void Material::SetMat4(const std::string& name, const glm::mat4& value) {
    uniforms[name] = value;
}

void Material::SetTexture(const std::string& name, unsigned int textureID, int slot) {
    textures[name] = {textureID, slot};
}

void Material::SetVec3Array(const std::string& name, const std::vector<glm::vec3>& values) {
    shader->Use();
    shader->SetVec3Array(name, values);
}



void Material::Apply() const {
    shader->Use();

    // Apply textures
    glBindTexture(GL_TEXTURE_2D,0);
    for (const auto& [name, texInfo] : textures) {
        glActiveTexture(GL_TEXTURE0 + texInfo.second);
        glBindTexture(GL_TEXTURE_2D, texInfo.first);
        shader->SetInt(name, texInfo.second);
    }

    // Apply uniforms
    for (const auto& [name, value] : uniforms) {
        ApplyUniform(name, value);
    }
}

void Material::ApplyUniform(const std::string& name, const UniformValue& value) const {
    std::visit([&](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, int>) {
            shader->SetInt(name, arg);
        } else if constexpr (std::is_same_v<T, float>) {
            shader->SetFloat(name, arg);
        } else if constexpr (std::is_same_v<T, glm::vec3>) {
            shader->SetVec3(name, arg);
        } else if constexpr (std::is_same_v<T, glm::vec4>) {
            shader->SetVec4(name, arg);
        } else if constexpr (std::is_same_v<T, glm::mat4>) {
            shader->SetMat4(name, arg);
        }
    }, value);
}
