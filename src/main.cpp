#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "utils.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "camera.hpp"

using namespace std;

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

GLfloat texture_buffer[] = {
    0.0f, 0.0f, 
    0.0f, 1.0f, 
    1.0f, 1.0f, 
    1.0f, 0.0f
};

const float width = 800;
const float height = 600;

glm::mat4 transform(1), model(1), view(1), projection(1);
camera cam;
glm::vec3 cube1_pos, cube2_pos;


int main(int argc, char **argv) {
    // Initializing glfw
    if(glfwInit() == GLFW_FALSE) {
        error("GLFW: Failed to initialize");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Creating window
    GLFWwindow *window = glfwCreateWindow(800, 600, "Hello Triangle", NULL, NULL);
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
    
    // Loading opengl function pointers
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glEnable(GL_DEPTH_TEST);
    
    
    // generate buffers
    GLuint vbo, vao;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    
    // load buffers
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    
    // set vertex attributes
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), ((void*)(3 * sizeof(float))));
    glEnableVertexAttribArray(1);    
    
    glBindVertexArray(0);
    
    
    // shaders
    GLuint vs, fs, prg;
    vs = createShader("shaders/triangle/vertex.glsl", GL_VERTEX_SHADER);
    fs = createShader("shaders/triangle/fragment.glsl", GL_FRAGMENT_SHADER);
    
    int success, length;
    char infolog[512];
    
    prg = linkShaders(vs, fs);
    glDeleteShader(vs);
    glDeleteShader(fs);
    
    // Set the uniforms
    glUseProgram(prg);
    glUniform1i(glGetUniformLocation(prg, "container"), 0);
    glUniform1i(glGetUniformLocation(prg, "smiley"), 1);

    // Transformations
    glm::vec3 cube1_pos = glm::vec3(0.0f, -1.0f, 0.0f);
    glm::vec3 cube1_color = glm::vec3(0.6f, 0.3f, 0.0f);
    glm::vec3 cube2_pos = glm::vec3(0.5f, 0.0f, 0.0f);
    glm::vec3 cube2_color = glm::vec3(1.0f, 1.0f, 1.0f);
    
    
    // main loop
    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.2f, 0.2f, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glfwPollEvents();
        
        glBindVertexArray(vao);
        glUseProgram(prg);
        view = cam.getViewMatrix();
        projection = glm::perspective(cam.getFov(), width / height, 0.1f, 100.0f);

        
        // Draw cube 1
        model = glm::mat4(1.0f);
        model = glm::translate(model, cube1_pos);
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        transform = projection * view * model;
        glUniformMatrix4fv(glGetUniformLocation(prg, "transform"), 1, GL_FALSE, glm::value_ptr(transform));
        glUniform3f(glGetUniformLocation(prg, "color"), cube1_color.x, cube1_color.y, cube1_color.z);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        // Draw cube 2
        model = glm::mat4(1.0f);
        model = glm::translate(model, cube2_pos);
        model = glm::scale(model, glm::vec3(0.25f));
        transform = projection * view * model;
        glUniformMatrix4fv(glGetUniformLocation(prg, "transform"), 1, GL_FALSE, glm::value_ptr(transform));
        glUniform3f(glGetUniformLocation(prg, "color"), cube2_color.x, cube2_color.y, cube2_color.z);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        glfwSwapBuffers(window);
    }

    // clear and return
    glfwTerminate();

    return 0;
}