#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include<glfw/glfw3.h>

// Hareket yönleri için enum
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UPWARD,
    DOWNWARD
};

class Camera {
public:
    // Kamera Vektörleri
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;

    float MovementSpeed = 2.5f;
    float MouseSensitivity = 0.1f;
    float Zoom = 45.0f;

    // Constructor
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);

    // --- Matris Fonksiyonları ---
    glm::mat4 getView() const;
    //glm::mat4 getProjection(float screenWidth, float screenHeight, float nearPlane = 0.1f, float farPlane = 100.0f) const;
    glm::mat4 getProjection(float nearPlane = 0.1f, float farPlane = 100.0f) const;


    // --- Pozisyon ve Bakış ---
    void setPosition(glm::vec3 newPos);
    void lookAt(glm::vec3 target);

    // --- Giriş İşleme ---
    void processKeyboard(Camera_Movement direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void processMouseScroll(float yoffset);

    void processMovement(GLFWwindow* window, float deltaTime);

    void setScreenSize(int w, int h);

private:
    // İçsel vektörleri (Front, Right, Up) Euler açılarına göre günceller
    void updateCameraVectors();
    float screenWidth;
    float screenHeight;
};

#endif