#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

struct Transform {
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;
    Transform() : position(0.0f),rotation(glm::quat(1.0f,0.0f,0.0f,0.0f)), scale(1.0f) {}
    void Scale(const glm::vec3& _scale) {
        scale *= _scale;
    }
    void Translate(const glm::vec3& delta) {
        position += delta;
    }
    void Rotate(float angle, const glm::vec3& axis) {
        rotation = glm::rotate(rotation, glm::radians(angle),axis);
    }
    void SetPosition(const glm::vec3& pos) {
        position = pos;
    }
    void SetRotation(const glm::quat& rot) {
        rotation = rot;
    }
    void SetScale(const glm::vec3& s) {
        scale = s;
    }
    glm::mat4 GetModelMatrix() const {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model = model * glm::mat4_cast(rotation);
        model = glm::scale(model, scale);
        return model;
    }
};


#endif