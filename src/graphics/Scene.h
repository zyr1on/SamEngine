#ifndef SCENE_H
#define SCENE_H

#include <entt/entt.hpp>
#include "GameObject.h"
#include "Camera.h"
#include <memory>
#include <vector>

class Scene {
public:
    Scene();

    GameObject CreateGameObject();
    void DestroyGameObject(GameObject& obj);

    void Update(float deltaTime);
    void Render(Camera& camera);

    entt::registry& GetRegistry() { return registry; }

    GameObject CreateCubeObject(std::shared_ptr<Shader> _shader, std::shared_ptr<Material> _material);
    GameObject CreateSphereObject(std::shared_ptr<Shader> _shader, std::shared_ptr<Material> _material);
    GameObject CreatePointLight();

private:
    entt::registry registry;
    
    void RenderMeshes(Camera& camera);
    void UpdateLights();
};

#endif