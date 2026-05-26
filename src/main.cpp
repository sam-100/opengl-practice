#include <iostream>
#include "GLFW/glfw3.h"
#include "utils.hpp"

using namespace std;


int main(int argc, char **argv) {
    if(glfwInit() == GLFW_FALSE) {
        error("GLFW: Failed to initialize");
    }
    GLFWwindow *window = glfwCreateWindow(800, 600, "Hello Triangle", NULL, NULL);
    if(window == nullptr) {
        glfwTerminate();
        error("GLFW: Failed to create window");
    }

    if(glfwSetKeyCallback(window, key_callback)) {
        error("GLFW: Failed to set key callback");
    };


    glfwMakeContextCurrent(window);
    
    int iteration = 0;
    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.2f, 0.2f, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}