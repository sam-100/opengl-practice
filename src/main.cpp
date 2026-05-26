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
    glfwInit();
    GLFWwindow *window = glfwCreateWindow(800, 600, "Hello Triangle", NULL, NULL);

    if(glfwSetKeyCallback(window, key_callback)) {
        error("GLFW: Failed to set key callback");
    }; 
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}