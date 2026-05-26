#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "utils.hpp"

using namespace std;

float vertex_buffer[] = {
    -0.5f, -0.5f, 0.0f, 
    0.5f, -0.5f, 0.0f, 
    0.0f, 0.5f, 0.0f
};

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
    if(glfwSetKeyCallback(window, key_callback)) {
        error("GLFW: Failed to set key callback");
    };

    // Loading opengl function pointers
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    

    // vertex buffer and vertex array
    GLuint vbo, vao;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vertex_buffer, GL_STATIC_DRAW);

    glBindVertexArray(vao);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);


    // shaders
    GLuint vs, fs, prg;
    const char *vs_src, *fs_src;
    int success, length;
    char infolog[512];

    vs = glCreateShader(GL_VERTEX_SHADER);
    vs_src = load_file("shaders/triangle/vertex.glsl");
    glShaderSource(vs, 1, &vs_src, nullptr);
    glCompileShader(vs);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vs, 512, &length, infolog);
        cerr << infolog << endl;
        error("OpenGL: Failed to compile vertex shader");
    }

    fs = glCreateShader(GL_FRAGMENT_SHADER);
    fs_src = load_file("shaders/triangle/fragment.glsl");
    glShaderSource(fs, 1, &fs_src, nullptr);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fs, 512, &length, infolog);
        cerr << infolog << endl;
        error("OpenGL: Failed to compile fragment shader");
    }

    prg = glCreateProgram();
    glAttachShader(prg, vs);
    glAttachShader(prg, fs);
    glLinkProgram(prg);
    glGetShaderiv(prg, GL_LINK_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(prg, 512, &length, infolog);
        cerr << infolog << endl;
        error("OpenGL: Failed to link shader program");
    }
    
    int iteration = 0;
    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.2f, 0.2f, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao);
        glUseProgram(prg);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwPollEvents();

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}