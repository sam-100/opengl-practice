#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "utils.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "camera.hpp"
#include "cube.hpp"
#include "sphere.hpp"

using namespace std;

const float width = 1200;
const float height = 900;

camera cam;
glm::mat4 projection = glm::perspective(cam.getFov(), width / height, 0.1f, 100.0f);

int main(int argc, char **argv) {
    /* ============= glfw setup and initialization  ============ */
    
    if(glfwInit() == GLFW_FALSE) {
        error("GLFW: Failed to initialize");
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Creating window
    GLFWwindow *window = glfwCreateWindow(width, height, "Hello Triangle", NULL, NULL);
    if(window == nullptr) {
        glfwTerminate();
        error("GLFW: Failed to create window");
    }
    glfwMakeContextCurrent(window);
    glfwFocusWindow(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // setting callbacks
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    /* ====================================================== */
    
    /* ============= opengl setup and initialization  ============ */
    // Loading opengl function pointers
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glEnable(GL_DEPTH_TEST);
    
    
    /* ====================================================== */
    
    cube cube(1.0f, 50.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.7f, 0.2f, 0.0f));
    sphere sphere(1.0f, 100.0f, glm::vec3(-3.0f, 0.0f, 2.0f), glm::vec3(0.0f));

    // main loop
    double prev_frame_time = glfwGetTime();
    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();
        
        double curr_time, delta_time;
        curr_time = glfwGetTime();
        delta_time = curr_time - prev_frame_time;
        prev_frame_time = curr_time;
        
        cube.update((float)delta_time);
        cube.render(cam.getViewMatrix(), projection, cam.getPosition());

        sphere.update((float)delta_time);
        sphere.render(cam.getViewMatrix(), projection, cam.getPosition());

        
        glfwSwapBuffers(window);
    }

    // clear and return
    glfwTerminate();

    return 0;
}