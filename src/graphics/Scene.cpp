#include "Scene.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "PointLight.h"
#include "MeshFactory.h"

Scene::Scene() {}

GameObject Scene::CreateGameObject() {
    entt::entity entity = registry.create();
    registry.emplace<Transform>(entity);
    return GameObject(this, entity);
}

GameObject Scene::CreateCubeObject(std::shared_ptr<Shader> _shader, std::shared_ptr<Material> _material) {
    GameObject cubeObj = CreateGameObject();
    auto cubeMesh = std::make_shared<Mesh>(MeshFactory::CreateCube());
    cubeObj.AddComponent<MeshRenderer>(cubeMesh,_material);
    return cubeObj;
}

GameObject Scene::CreateSphereObject(std::shared_ptr<Shader> _shader, std::shared_ptr<Material> _material) {
    GameObject sphereObject = CreateGameObject();
    auto sphereMesh = std::make_shared<Mesh>(MeshFactory::CreateSphere());
    sphereObject.AddComponent<MeshRenderer>(sphereMesh,_material);    
    return sphereObject;
}

GameObject Scene::CreatePointLight() {
    GameObject lightObj = CreateGameObject();
    lightObj.AddComponent<PointLight>(glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);
    return lightObj;
}



void Scene::DestroyGameObject(GameObject& obj) {
    registry.destroy(obj.GetEntity());
}

void Scene::Update(float deltaTime) {
    // Update logic can be added here
}

void Scene::Render(Camera& camera) {
    UpdateLights();
    RenderMeshes(camera);
}

void Scene::UpdateLights() {
    // Collect light data for shaders if needed
}

void Scene::RenderMeshes(Camera& camera) {
    glm::mat4 view = camera.getView();
    glm::mat4 projection = camera.getProjection();

    // Tüm ışıkları topla
    std::vector<glm::vec3> lightPositions;
    std::vector<glm::vec3> lightColors;
    
    auto lights = registry.view<Transform, PointLight>();
    for (auto lightEntity : lights) {
        if (lightPositions.size() >= 4) break; // Max 4 ışık
        
        auto& lightTransform = lights.get<Transform>(lightEntity);
        auto& light = lights.get<PointLight>(lightEntity);
        
        lightPositions.push_back(lightTransform.position);
        lightColors.push_back(light.color * light.intensity);
    }

    // Mesh'leri render et
    auto view_meshes = registry.view<Transform, MeshRenderer>();
    
    for (auto entity : view_meshes) {
        auto& transform = view_meshes.get<Transform>(entity);
        auto& renderer = view_meshes.get<MeshRenderer>(entity);

        auto material = renderer.GetMaterial();
        if (!material) continue;

        material->SetMat4("model", transform.GetModelMatrix());
        material->SetMat4("view", view);
        material->SetMat4("projection", projection);
        material->SetVec3("viewPos", camera.Position);

        // Işıkları set et
        if (!lightPositions.empty()) {
            material->SetInt("u_LightCount", static_cast<int>(lightPositions.size()));
            
            // Array uniformlar için Shader.h'ye yeni fonksiyon ekle
            material->SetVec3Array("u_LightPositions", lightPositions);
            material->SetVec3Array("u_LightColors", lightColors);
        } else {
            material->SetInt("u_LightCount", 0);
        }

        renderer.Render();
    }
}