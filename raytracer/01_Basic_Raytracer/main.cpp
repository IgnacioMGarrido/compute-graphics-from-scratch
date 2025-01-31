#include <GLFW/glfw3.h>
#include <iostream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

void window_close_callback(GLFWwindow* window) {
    std::cout << "Closing window..." << std::endl;
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Error: Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Window", nullptr, nullptr);
    if (!window) {
        std::cerr << "Error: Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowCloseCallback(window, window_close_callback);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    std::cout << "Application terminated." << std::endl;
    return 0;
}
