#include "Time.h"
#include <GLFW/glfw3.h> // GLFW kullanıyorsan

// Statik değişkenlerin ilklendirilmesi
float Time::deltaTime = 0.0f;
float Time::lastFrame = 0.0f;

void Time::update() {
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}