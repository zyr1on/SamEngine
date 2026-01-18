#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "core/Window.h"
#include "graphics/MeshFactory.h"
#include "graphics/Shader.h"
#include "graphics/Mesh.h"
#include "graphics/Camera.h"
#include "core/Time.h"
#include "graphics/TextureManager.h"

int main()
{
    Window window;
    Camera camera;
    window.setCamera(&camera);

    Shader cubeShader("../assets/shaders/vertexShader.glsl", "../assets/shaders/unlit_texture.glsl", "CubeShader");
    Mesh cubeMesh(MeshFactory::CreateCube());
    
    
    cubeShader.use();
    glm::mat4 model = glm::translate(glm::mat4(1.0f),glm::vec3(0.0f,0.0f,0.0f));
    GLuint woodTexture = TextureManager::getInstance().loadTexture("../assets/textures/container.jpg");
    glActiveTexture(GL_TEXTURE0);
    

    while (!window.shouldClose())
    {
        window.clear();
        camera.processMovement(window.getNativeWindow(), Time::deltaTime);
        
        glBindTexture(GL_TEXTURE_2D,woodTexture);
        
        cubeShader.setUniform("model",model);
        cubeShader.setUniform("projection",camera.getProjection());
        cubeShader.setUniform("view",camera.getView());
        
        cubeMesh.Draw();

        glBindTexture(GL_TEXTURE_2D, 0);

        window.update();
    }
    return 0;
}
