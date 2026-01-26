#include "Window.h"
#include "core/Time.h"      // Daha önce yazdığımız Time sınıfı
#include "graphics/Camera.h"
#include <iostream>

Window::Window(int width, int height, const char* title) 
    : m_width(width), m_height(height), m_camera(nullptr) {
    
    m_lastX = width / 2.0f;
    m_lastY = height / 2.0f;

    if (!init(title)) {
        std::cerr << "Window Initialization Failed!" << std::endl;
    }
}

bool Window::init(const char* title) {
    if (!glfwInit()) return false;

    // OpenGL Versiyon Ayarları (Opsiyonel ama önerilir)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(m_width, m_height, title, nullptr, nullptr);
    if (!m_window) {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_window);
    
    // GLAD Yüklemesi
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    // --- KRİTİK NOKTA: User Pointer ---
    // Bu 'this' (yani şu anki Window nesnesi) pointer'ını GLFW penceresine iliştiriyoruz.
    // Böylece statik callback fonksiyonları içinden bu nesneye ulaşabileceğiz.
    glfwSetWindowUserPointer(m_window, this);

    // Callback Kayıtları
    glfwSetCursorPosCallback(m_window, mouseCallback);
    glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);
    glfwSetKeyCallback(m_window, keyCallback);

    // Pencere Ayarları
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Mouse'u ekrana hapseder
    glfwSwapInterval(1); // V-Sync Açık
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    return true;
}

void Window::setCamera(Camera* camera) {
    m_camera = camera;
    camera->setScreenSize(m_width,m_height);
}

void Window::update() {
    glfwSwapBuffers(m_window);
    Time::update(); // DeltaTime hesaplanır
    glfwPollEvents();
}

void Window::clear() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(m_window);
}

Window::~Window() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

// --- CALLBACK IMPLEMENTASYONLARI ---

void Window::mouseCallback(GLFWwindow* window, double xposIn, double yposIn) {
    // GLFW'den Window nesnemizi geri alıyoruz
    Window* handler = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (!handler || !handler->m_camera) return;

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (handler->m_firstMouse) {
        handler->m_lastX = xpos;
        handler->m_lastY = ypos;
        handler->m_firstMouse = false;
    }

    float xoffset = xpos - handler->m_lastX;
    float yoffset = handler->m_lastY - ypos; // Y ekseni OpenGL'de aşağıdan yukarıyadır

    handler->m_lastX = xpos;
    handler->m_lastY = ypos;

    handler->m_camera->processMouseMovement(xoffset, yoffset);
}

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    Window* handler = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (handler) {
        handler->m_width = width;
        handler->m_height = height;
    }
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}