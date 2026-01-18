#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>


// Forward declaration (Header kirliliğini önlemek için sadece ismini veriyoruz)
class Camera;

class Window {
public:
    Window(int width = 800, int height = 600, const char* title = "SamEngine");
    ~Window();

    // Temel döngü fonksiyonları
    bool shouldClose() const;
    void update();
    void clear() const;

    // Kamera bağlantısı
    void setCamera(Camera* camera);

    // Getters
    GLFWwindow* getNativeWindow() const { return m_window; }
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }

private:
    GLFWwindow* m_window;
    Camera* m_camera = nullptr;

    int m_width, m_height;
    
    // Mouse durumu (Sınıf içinde kapsüllenmiş)
    float m_lastX, m_lastY;
    bool m_firstMouse = true;

    bool init(const char* title);

    // GLFW Callback'leri (Statik olmaları zorunludur)
    static void mouseCallback(GLFWwindow* window, double xposIn, double yposIn);
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif