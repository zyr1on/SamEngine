#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <entt/entt.hpp>
#include "Transform.h"
#include "MeshRenderer.h"
#include "PointLight.h"
#include <memory>

class Scene; // Forward declaration

class GameObject {
public:
    GameObject(Scene* scene, entt::entity entity);

    Transform* transform; // default struct that every gameobject have.
    
    template<typename T, typename... Args>
    T& AddComponent(Args&&... args) {
        return registry->emplace<T>(entity, std::forward<Args>(args)...);
    }

    template<typename T>
    T& GetComponent() {
        return registry->get<T>(entity);
    }

    template<typename T>
    bool HasComponent() const {
        return registry->all_of<T>(entity);
    }

    template<typename T>
    void RemoveComponent() {
        registry->remove<T>(entity);
    }

    //Transform& GetTransform() { return GetComponent<Transform>(); }

    entt::entity GetEntity() const { return entity; }


private:
    entt::entity entity;
    entt::registry* registry;
};

#endif