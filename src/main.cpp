#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "graphics/Scene.h"
#include "graphics/MeshFactory.h"
#include "graphics/Shader.h"
#include "graphics/Material.h"
#include "graphics/Camera.h"
#include "core/Window.h"
#include "core/Time.h"
#include "graphics/TextureManager.h"

int main()
{
    Window window;
    Camera camera;
    Scene scene;
    window.setCamera(&camera);
    camera.setPosition(glm::vec3(3.0f, 3.0f, 3.0f));
    camera.lookAt(glm::vec3(0.0f, 0.0f, 0.0f));

    auto litShader = std::make_shared<Shader>("../assets/shaders/vertexShader.glsl", "../assets/shaders/shader.frag");
    auto unlitShader = std::make_shared<Shader>("../assets/shaders/vertexShader.glsl", "../assets/shaders/unlit.glsl");

    auto litMaterial = std::make_shared<Material>(litShader);
    auto unlitMaterial = std::make_shared<Material>(unlitShader);

    litMaterial->SetFloat("u_AmbientStrength", 0.1f);
    litMaterial->SetFloat("u_SpecularStrength", 0.5f);
    litMaterial->SetFloat("u_Shininess", 32.0f);

    unlitMaterial->SetVec3("uColor", glm::vec3(1.0f, 0.0f, 0.0f));

    unsigned int texture = TextureManager::getInstance().loadTexture("../assets/textures/container.jpg");
    litMaterial->SetTexture("texture_diffuse1", texture, 0);

    GameObject cubeObj = scene.CreateCubeObject(litShader, litMaterial);
    GameObject sphereObj = scene.CreateSphereObject(unlitShader, unlitMaterial);

    sphereObj.transform->position = glm::vec3(3.0f, 0.0f, 0.0f);
    sphereObj.transform->scale = glm::vec3(0.5f, 0.5f, 0.5f);

    GameObject lightObj = scene.CreatePointLight();
    lightObj.GetComponent<PointLight>().color = glm::vec3(1.0f, 0.0f, 0.0f);
    lightObj.transform->position = sphereObj.transform->position;

    while (!window.shouldClose())
    {
        window.clear();
        camera.processMovement(window.getNativeWindow(), Time::deltaTime);

        scene.Update(Time::deltaTime);
        scene.Render(camera);

        window.update();
    }

    return 0;
}