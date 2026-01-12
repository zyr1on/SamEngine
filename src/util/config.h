#ifndef CONFIG_H
#define CONFIG_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

#include "graphics/MeshFactory.h"
#include "graphics/Shader.h"
#include "graphics/Mesh.h"
#include "graphics/Camera.h"


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);

GLFWwindow* initWindow(int w, int h, const char* name) 
{
     if (!glfwInit()) {
        std::cerr << "GLFW başlatılamadı!" << std::endl;
        return nullptr;
    }

    GLFWwindow* window = glfwCreateWindow(w, h, name, nullptr, nullptr);
    if (!window) {
        std::cerr << "Pencere oluşturulamadı!" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    return window;

}

void updateWindow(GLFWwindow* window) {
    glfwSwapBuffers(window);
    glfwPollEvents();
}
void destroyWindow(GLFWwindow* window) {
    glfwDestroyWindow(window);
    glfwTerminate();
}




#endif
