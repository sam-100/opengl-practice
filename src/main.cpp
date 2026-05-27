#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "utils.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace std;

GLfloat position_buffer[] = {
    -0.5f, -0.5f, 0.0f, 
    -0.5f,  0.5f, 0.0f, 
     0.5f,  0.5f, 0.0f, 
     0.5f, -0.5f, 0.0f
};

GLuint element_buffer[] = {
    0, 1, 2, 
    0, 2, 3
};

GLfloat color_buffer[] = {
    1.0, 0.0, 0.0, 1.0, 
    0.0, 1.0, 0.0, 1.0, 
    0.0, 0.0, 1.0, 1.0, 
    0.5, 0.5, 0.5, 1.0
};

GLfloat texture_buffer[] = {
    0.0f, 0.0f, 
    0.0f, 1.0f, 
    1.0f, 1.0f, 
    1.0f, 0.0f
};

const int vertex_count = 12;
const int index_count = 6;

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

    // setting callbacks
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);
    

    // Loading opengl function pointers
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    

    // generate buffers
    GLuint pos_bo, vao, index_bo, color_bo, texture_bo;
    glGenBuffers(1, &pos_bo);
    glGenBuffers(1, &index_bo);
    glGenBuffers(1, &color_bo);
    glGenBuffers(1, &texture_bo);
    glGenVertexArrays(1, &vao);

    // load buffers
    glBindBuffer(GL_ARRAY_BUFFER, pos_bo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(position_buffer), position_buffer, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, color_bo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer), color_buffer, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, texture_bo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texture_buffer), texture_buffer, GL_STATIC_DRAW);

    // generate and load texture
    GLuint tex_container, tex_smiley;
    tex_container = generate_texture("assets/container.jpg");
    tex_smiley = generate_texture("assets/smiley.png");

    // GLuint tex_smiley = generate_texture("assets/container.jpg");
    
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_bo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(element_buffer), element_buffer, GL_STATIC_DRAW);
    glBindVertexArray(0);
    
    // set vertex attributes
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, pos_bo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, color_bo);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, texture_bo);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(2);
    

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


    
    // main loop
    int iterator;
    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.2f, 0.2f, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex_container);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, tex_smiley);
        glBindVertexArray(vao);
        glUseProgram(prg);
        
        // Transformations
        double curr_time = glfwGetTime();
        glm::mat4 transform(1);
        transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.0f));
        transform = glm::rotate(transform, (float)curr_time, glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::translate(transform, glm::vec3(1.0, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(prg, "transform"), 1, GL_FALSE, glm::value_ptr(transform));

        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwPollEvents();

        glfwSwapBuffers(window);
    }

    // clear and return
    glfwTerminate();

    return 0;
}