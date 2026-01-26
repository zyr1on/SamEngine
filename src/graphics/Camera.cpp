#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) 
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)), Position(position), WorldUp(up), Yaw(yaw), Pitch(pitch) {
    updateCameraVectors();
}

glm::mat4 Camera::getView() const {
    return glm::lookAt(Position, Position + Front, Up);
}

glm::mat4 Camera::getProjection(float nearPlane, float farPlane) const {
    //return glm::perspective(glm::radians(Zoom), screenWidth / screenHeight, nearPlane, farPlane);
    return glm::perspective(glm::radians(Zoom), screenWidth / screenHeight, nearPlane, farPlane);

}

void Camera::setPosition(glm::vec3 newPos) {
    Position = newPos;
}

void Camera::lookAt(glm::vec3 target) {
    Front = glm::normalize(target - Position);
    
    Pitch = glm::degrees(asin(Front.y));
    Yaw = glm::degrees(atan2(Front.z, Front.x));

    updateCameraVectors();
}

void Camera::processKeyboard(Camera_Movement direction, float deltaTime) {
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)  Position += Front * velocity;
    if (direction == BACKWARD) Position -= Front * velocity;
    if (direction == LEFT)     Position -= Right * velocity;
    if (direction == RIGHT)    Position += Right * velocity;
    if (direction == UPWARD)   Position += WorldUp * velocity;
    if (direction == DOWNWARD) Position -= WorldUp * velocity;
}

void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw   += xoffset;
    Pitch += yoffset;

    if (constrainPitch) {
        if (Pitch > 89.0f)  Pitch = 89.0f;
        if (Pitch < -89.0f) Pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset) {
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)  Zoom = 1.0f;
    if (Zoom > 45.0f) Zoom = 45.0f;
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    
    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));  
    Up    = glm::normalize(glm::cross(Right, Front));
}

void Camera::processMovement(GLFWwindow* window, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        processKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        processKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        processKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        processKeyboard(RIGHT, deltaTime);
    if(glfwGetKey(window,GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        MovementSpeed = 5.0f;
    else
        MovementSpeed = 2.5f;
}

void Camera::setScreenSize(int w, int h){
    screenHeight = h;
    screenWidth = w;
}