#include "Shader.h"

static std::string ReadFile(const std::string &path)
{
    std::ifstream file(path, std::ios::in | std::ios::binary);
    if (!file)
    {
        std::cerr << "[Shader] Dosya acilamadi: " << path << std::endl;
        return {};
    }

    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

Shader::Shader(std::string_view vertexPath,
               std::string_view fragmentPath,
               std::string shaderName)
    : shaderName(std::move(shaderName)), m_ProgramID(0)
{
    std::string vertexSource = ReadFile(std::string(vertexPath));
    std::string fragmentSource = ReadFile(std::string(fragmentPath));

    if (vertexSource.empty() || fragmentSource.empty())
    {
        std::cerr << "[Shader] Shader kaynaklari bos!" << std::endl;
        return;
    }

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    compileShader(vertexShader, GL_VERTEX_SHADER);
    compileShader(fragmentShader, GL_FRAGMENT_SHADER);

    const char *vSrc = vertexSource.c_str();
    const char *fSrc = fragmentSource.c_str();

    glShaderSource(vertexShader, 1, &vSrc, nullptr);
    glShaderSource(fragmentShader, 1, &fSrc, nullptr);

    glCompileShader(vertexShader);
    checkCompileErrors(GL_VERTEX_SHADER, vertexSource);

    glCompileShader(fragmentShader);
    checkCompileErrors(GL_FRAGMENT_SHADER, fragmentSource);

    createProgram();
    cacheUniforms();
}

Shader::~Shader()
{
    if (m_ProgramID)
        glDeleteProgram(m_ProgramID);

    if (vertexShader)
        glDeleteShader(vertexShader);

    if (fragmentShader)
        glDeleteShader(fragmentShader);
}

void Shader::use()
{
    glUseProgram(m_ProgramID);
}

void Shader::createProgram()
{
    m_ProgramID = glCreateProgram();

    glAttachShader(m_ProgramID, vertexShader);
    glAttachShader(m_ProgramID, fragmentShader);
    glLinkProgram(m_ProgramID);

    GLint success;
    glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[1024];
        glGetProgramInfoLog(m_ProgramID, 1024, nullptr, infoLog);
        std::cerr << "[Shader] Program link hatasi (" << shaderName << "):\n"
                  << infoLog << std::endl;
    }

    glDetachShader(m_ProgramID, vertexShader);
    glDetachShader(m_ProgramID, fragmentShader);
}

void Shader::checkCompileErrors(GLenum type, std::string & /*source*/)
{
    GLint success;
    char infoLog[1024];

    GLuint shader = (type == GL_VERTEX_SHADER) ? vertexShader : fragmentShader;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        std::cerr << "[Shader] "
                  << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment")
                  << " shader compile hatasi (" << shaderName << "):\n"
                  << infoLog << std::endl;
    }
}

GLuint Shader::compileShader(GLuint id, GLenum /*type*/)
{
    return id;
}

void Shader::cacheUniforms()
{
    GLint count;
    glGetProgramiv(m_ProgramID, GL_ACTIVE_UNIFORMS, &count);

    char name[256];
    GLsizei length;
    GLint size;
    GLenum type;

    for (GLint i = 0; i < count; i++)
    {
        glGetActiveUniform(m_ProgramID, i, sizeof(name), &length, &size, &type, name);
        GLint location = glGetUniformLocation(m_ProgramID, name);
        m_UniformCache.emplace(name, location);
    }
}

// ===================== UNIFORM SETTERS =====================

void Shader::addUniform(const std::string &name)
{
    // Zaten cache'de varsa tekrar ekleme
    if (m_UniformCache.find(name) != m_UniformCache.end())
        return;

    GLint location = glGetUniformLocation(m_ProgramID, name.c_str());

    if (location == -1)
    {
        std::cerr << "[Shader] Uniform bulunamadi: "
                  << name << " (" << shaderName << ")" << std::endl;
        return;
    }

    m_UniformCache.emplace(name, location);
}

void Shader::setUniform(std::string_view name, int value)
{
    auto it = m_UniformCache.find(std::string(name));
    if (it != m_UniformCache.end())
        glUniform1i(it->second, value);
}

void Shader::setUniform(std::string_view name, float value)
{
    auto it = m_UniformCache.find(std::string(name));
    if (it != m_UniformCache.end())
        glUniform1f(it->second, value);
}

void Shader::setUniform(std::string_view name, bool value)
{
    setUniform(name, static_cast<int>(value));
}

void Shader::setUniform(std::string_view name, const glm::mat4 &aMat)
{
    auto it = m_UniformCache.find(std::string(name));
    if (it != m_UniformCache.end())
        glUniformMatrix4fv(it->second, 1, GL_FALSE, glm::value_ptr(aMat));
}

void Shader::setUniform(std::string_view name, const glm::mat3 &aMat)
{
    auto it = m_UniformCache.find(std::string(name));
    if (it != m_UniformCache.end())
        glUniformMatrix3fv(it->second, 1, GL_FALSE, glm::value_ptr(aMat));
}

void Shader::setUniform(std::string_view name, const glm::vec3 &aVec)
{
    auto it = m_UniformCache.find(std::string(name));
    if (it != m_UniformCache.end())
        glUniform3fv(it->second, 1, glm::value_ptr(aVec));
}

void Shader::setUniform(std::string_view name, const glm::vec4 &aVec)
{
    auto it = m_UniformCache.find(std::string(name));
    if (it != m_UniformCache.end())
        glUniform4fv(it->second, 1, glm::value_ptr(aVec));
}
