#include "config.h"

float deltaTime = 0.0f;
float lastFrame = 0.0f;
float lastX = 400, lastY = 300; // Ekran ortası başlangıç
bool firstMouse = true;


Camera camera;
int main()
{

    GLFWwindow *window = initWindow(800, 600, "OpenGL");
    if (!window)
    {
        std::cerr << "Window init failed!" << std::endl;
        return -1;
    }

    Shader ourShader("../assets/shaders/vertexShader.glsl", "../assets/shaders/unlit.glsl");
    
    camera.setPosition(glm::vec3(3.0f, 3.0f, 3.0f));
    camera.lookAt(glm::vec3(0.0f, 0.0f, 0.0f));

    MeshData cubeData = MeshFactory::CreatePlane();
    Mesh cubeMesh(cubeData);

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        camera.processMovement(window,deltaTime);

        ourShader.use();
        ourShader.setUniform("model", model);
        ourShader.setUniform("uColor", glm::vec3(0.5f, 0.5f, 0.5f));

        ourShader.setUniform("projection", camera.getProjection(800, 600));
        ourShader.setUniform("view", camera.getView());
        cubeMesh.Draw();

        updateWindow(window);
    }
    destroyWindow(window);

    return 0;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // Y ekseni aşağıdan yukarıya artar, bu yüzden ters çeviriyoruz

    lastX = xpos;
    lastY = ypos;

    camera.processMouseMovement(xoffset, yoffset);
}