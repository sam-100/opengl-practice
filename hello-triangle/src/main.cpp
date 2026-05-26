#include <iostream>
#include "GLFW/glfw3.h"

using namespace std;


int main(int argc, char **argv) {
    glfwInit();
    GLFWwindow *window = glfwCreateWindow(800, 600, "Hello Triangle", NULL, NULL);
    while(true);

    return 0;
}