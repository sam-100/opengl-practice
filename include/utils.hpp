#ifndef UTILS_HPP
#define UTILS_HPP

#include "GLFW/glfw3.h"


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void error(const char *msg);

#endif