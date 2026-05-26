#include <iostream>
#include "GLFW/glfw3.h"

using namespace std;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        return;
    }
}

void error(const char *msg) {
    cerr << "Error: " << msg << endl;
    exit(1);
}

int main(int argc, char **argv) {
    if(glfwInit() == GLFW_FALSE) {
        error("GLFW: Failed to initialize");
    }
    GLFWwindow *window = glfwCreateWindow(800, 600, "Hello Triangle", NULL, NULL);
    if(window == nullptr) {
        error("GLFW: Failed to create window");
    }

    if(glfwSetKeyCallback(window, key_callback)) {
        error("GLFW: Failed to set key callback");
    };


    glfwMakeContextCurrent(window);
    
    int iteration = 0;
    while(!glfwWindowShouldClose(window)) {
        glClearColor((float)((iteration++)%256)/256, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}