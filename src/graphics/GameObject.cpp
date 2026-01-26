#include "GameObject.h"
#include "Scene.h"

GameObject::GameObject(Scene* scene, entt::entity entity) 
    : entity(entity), registry(&scene->GetRegistry()) 
    {
        transform = &GetComponent<Transform>();
        
    }