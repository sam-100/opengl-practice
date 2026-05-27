#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "utils.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

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
glm::vec3 cam_position, cam_right_direction, cam_front_direction;

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
    
    // generate and load texture
    GLuint tex_container, tex_smiley;
    tex_container = generate_texture("assets/container.jpg");
    tex_smiley = generate_texture("assets/smiley.png");
        
    
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
    cam_position = glm::vec3(0.0f, 0.0f, 3.0f);
    cam_front_direction = glm::vec3(0.0f, 0.0f, -1.0f);
    cam_right_direction = glm::vec3(1.0f, 0.0f, 0.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
    // model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    projection = glm::perspective(glm::radians(60.0f), width / height, 0.1f, 100.0f);
    
    // main loop
    int iterator;
    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.2f, 0.2f, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex_container);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, tex_smiley);
        glBindVertexArray(vao);
        glUseProgram(prg);
        
        // Transformations
        // model = glm::rotate(model, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        // view = glm::lookAt(cam_position, cam_position + cam_front_direction, glm::normalize(glm::cross(cam_right_direction, cam_front_direction)));
        view = glm::lookAt(
            cam_position, 
            cam_position + cam_front_direction, 
            glm::normalize(glm::cross(cam_right_direction,cam_front_direction))
        );
        transform = projection * view * model;
        glUniformMatrix4fv(glGetUniformLocation(prg, "transform"), 1, GL_FALSE, glm::value_ptr(transform));
        
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwPollEvents();

        glfwSwapBuffers(window);
    }

    // clear and return
    glfwTerminate();

    return 0;
}