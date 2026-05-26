
#include "utils.hpp"
#include <iostream>

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


