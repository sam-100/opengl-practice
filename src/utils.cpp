
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

const char* load_file(const char* file_path) {
    FILE* file = fopen(file_path, "rb");

    if (file == nullptr) {
        return nullptr;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char* buffer = new char[size + 1];

    fread(buffer, 1, size, file);
    buffer[size] = '\0';

    fclose(file);

    return buffer;
}