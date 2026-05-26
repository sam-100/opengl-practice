#ifndef UTILS_HPP
#define UTILS_HPP

#include "glad/glad.h"
#include "GLFW/glfw3.h"


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void error(const char *msg);
const char *load_file(const char *file_path);
GLuint generate_texture(const char *file_name);

#endif