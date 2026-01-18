#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

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

    Shader sunShader("../assets/shaders/vertexShader.glsl", "../assets/shaders/unlit_texture.glsl","SunShader");
    sunShader.setUniform("uTexture",0);
    Shader cubeShader("../assets/shaders/vertexShader.glsl","../assets/shaders/basic_lit.glsl","CubeShader");
    cubeShader.setUniform("texture_diffuse1",0);

    unsigned int sunTexture = TextureManager::getInstance().loadTexture("../assets/textures/sun.jpg");
    unsigned int woodTexture = TextureManager::getInstance().loadTexture("../assets/textures/container.jpg");

    camera.setPosition(glm::vec3(3.0f, 3.0f, 3.0f));
    camera.lookAt(glm::vec3(0.0f, 0.0f, 0.0f));
    
    Mesh sunMesh(MeshFactory::CreateSphere());
    Mesh cubeMesh(MeshFactory::CreateCube());

    
    glm::mat4 cubeModel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    
    glm::mat4 sunModel = glm::translate(glm::mat4(1.0f),glm::vec3(4.5f,3.0f,2.7f));
    
    sunModel = glm::scale(sunModel,glm::vec3(0.5f,0.5f,0.5f));
    while (!window.shouldClose())
    {
        window.clear();
        camera.processMovement(window.getNativeWindow(),Time::deltaTime);

        sunShader.use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,sunTexture);
        
        sunShader.setUniform("model",sunModel);
        sunShader.setUniform("view",camera.getView());
        sunShader.setUniform("projection",camera.getProjection(800.0f,600.0f,0.1f,100.0f));
        sunMesh.Draw();
        glBindTexture(GL_TEXTURE_2D,0);


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,woodTexture);
        cubeShader.use();
        cubeShader.setUniform("model",cubeModel);
        cubeShader.setUniform("view",camera.getView());
        cubeShader.setUniform("projection",camera.getProjection(800.0f,600.0f,0.1f,100.0f));
        cubeShader.setUniform("lightPos",glm::vec3(4.5f, 3.0f, 2.7f));
        cubeShader.setUniform("viewPos",camera.Position);
        cubeShader.setUniform("lightColor",glm::vec3(1.0f,1.0f,1.0f));
        
        cubeMesh.Draw();
        glBindTexture(GL_TEXTURE_2D,0);
        

        window.update();
    }
    
    return 0;
}
