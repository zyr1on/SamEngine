#include "graphics/Shader.h"

// Yardımcı Fonksiyon: Dosyadan Metin Oku
static std::string ReadFile(const std::string& path) {
    std::ifstream file(path, std::ios::in | std::ios::binary);
    if (!file) {
        std::cerr << "[Shader::Error] Dosya acilamadi: " << path << std::endl;
        return "";
    }
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

Shader::Shader(std::string_view vertexPath, std::string_view fragmentPath, std::string shaderName)
    : shaderName(std::move(shaderName)), m_ProgramID(0), vertexShader(0), fragmentShader(0) 
{
    // 1. Kaynak Kodlarını Oku
    std::string vSourceStr = ReadFile(std::string(vertexPath));
    std::string fSourceStr = ReadFile(std::string(fragmentPath));

    if (vSourceStr.empty() || fSourceStr.empty()) {
        std::cerr << "[Shader::" << this->shaderName << "] HATA: Kaynaklar bos!" << std::endl;
        return;
    }

    const char* vSrc = vSourceStr.c_str();
    const char* fSrc = fSourceStr.c_str();

    // 2. Vertex Shader Derle
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vSrc, nullptr);
    glCompileShader(vertexShader);
    checkCompileErrors(GL_VERTEX_SHADER, vSourceStr);
    std::cout << "[Shader::" << this->shaderName << "] VertexShader compiled" << std::endl;

    // 3. Fragment Shader Derle
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fSrc, nullptr);
    glCompileShader(fragmentShader);
    checkCompileErrors(GL_FRAGMENT_SHADER, fSourceStr);
    std::cout << "[Shader::" << this->shaderName << "] FragmentShader compiled" << std::endl;

    // 4. Program Oluştur ve Linkle
    createProgram();

    // 5. Uniformları Cache'le
    cacheUniforms();
}

Shader::~Shader() {
    std::string currentName = this->shaderName;

    if (m_ProgramID) {
        glDeleteProgram(m_ProgramID);
        //std::cout << "[Shader::" << currentName << "] Program (" << currentName << ") deleted." << std::endl;
    }
    if (vertexShader) {
        glDeleteShader(vertexShader);
        //std::cout << "[Shader::" << currentName << "] Vertex shader (" << currentName << ") deleted." << std::endl;
    }
    if (fragmentShader) {
        glDeleteShader(fragmentShader);
        //std::cout << "[Shader::" << currentName << "] Fragment shader (" << currentName << ") deleted." << std::endl;
    }
    std::cout << "[Shader::" << currentName << "] Shader Program, vertex and fragment shader succesfully deleted." << std::endl;
}

void Shader::use() {
    glUseProgram(m_ProgramID);
}

void Shader::createProgram() {
    m_ProgramID = glCreateProgram();
    glAttachShader(m_ProgramID, vertexShader);
    glAttachShader(m_ProgramID, fragmentShader);
    glLinkProgram(m_ProgramID);

    GLint success;
    glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetProgramInfoLog(m_ProgramID, 1024, nullptr, infoLog);
        std::cerr << "[Shader::" << shaderName << "] Program link hatasi:\n" << infoLog << std::endl;
    } else {
        std::cout << "[Shader::" << shaderName << "] Program linked successfully" << std::endl;
    }

    glDetachShader(m_ProgramID, vertexShader);
    glDetachShader(m_ProgramID, fragmentShader);
}

void Shader::cacheUniforms() {
    GLint count;
    glGetProgramiv(m_ProgramID, GL_ACTIVE_UNIFORMS, &count);

    std::cout << "[Shader::" << shaderName << "] Uniforms cached :" << std::endl;

    char name[256];
    GLsizei length;
    GLint size;
    GLenum type;

    for (GLint i = 0; i < count; i++) {
        glGetActiveUniform(m_ProgramID, i, sizeof(name), &length, &size, &type, name);
        GLint location = glGetUniformLocation(m_ProgramID, name);
        m_UniformCache[name] = (unsigned int)location;
        std::cout << "    - " << name << std::endl;
    }
    std::cout << std::endl;
}

void Shader::checkCompileErrors(GLenum type, std::string& source) {
    GLint success;
    char infoLog[1024];
    GLuint shader = (type == GL_VERTEX_SHADER) ? vertexShader : fragmentShader;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        std::cerr << "[Shader::" << shaderName << "] " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") 
                  << " compile hatasi:\n" << infoLog << std::endl;
    }
}

GLuint Shader::compileShader(GLuint id, GLenum type) {
    return id; 
}

// ===================== UNIFORM SETTERS =====================

void Shader::addUniform(const std::string& name) {
    m_UniformCache[name] = glGetUniformLocation(m_ProgramID, name.c_str());
}

void Shader::setUniform(std::string_view name, int value) {
    auto it = m_UniformCache.find(std::string(name));
    if (it != m_UniformCache.end()) glUniform1i(it->second, value);
}

void Shader::setUniform(std::string_view name, float value) {
    auto it = m_UniformCache.find(std::string(name));
    if (it != m_UniformCache.end()) glUniform1f(it->second, value);
}

void Shader::setUniform(std::string_view name, bool value) {
    setUniform(name, (int)value);
}

void Shader::setUniform(std::string_view name, const glm::mat4& aMat) {
    auto it = m_UniformCache.find(std::string(name));
    if (it != m_UniformCache.end()) glUniformMatrix4fv(it->second, 1, GL_FALSE, glm::value_ptr(aMat));
}

void Shader::setUniform(std::string_view name, const glm::mat3& aMat) {
    auto it = m_UniformCache.find(std::string(name));
    if (it != m_UniformCache.end()) glUniformMatrix3fv(it->second, 1, GL_FALSE, glm::value_ptr(aMat));
}

void Shader::setUniform(std::string_view name, const glm::vec3& aVec) {
    auto it = m_UniformCache.find(std::string(name));
    if (it != m_UniformCache.end()) glUniform3fv(it->second, 1, glm::value_ptr(aVec));
}

void Shader::setUniform(std::string_view name, const glm::vec4& aVec) {
    auto it = m_UniformCache.find(std::string(name));
    if (it != m_UniformCache.end()) glUniform4fv(it->second, 1, glm::value_ptr(aVec));
}