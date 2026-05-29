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
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};


GLfloat texture_buffer[] = {
    0.0f, 0.0f, 
    0.0f, 1.0f, 
    1.0f, 1.0f, 
    1.0f, 0.0f
};

const float width = 1200;
const float height = 900;

glm::mat4 transform(1), model_object(1), model_lighting(1), view(1), projection(1);
camera cam;
glm::vec3 object_cube, light_cube;

// Transformations
glm::vec3 cube_object_pos = glm::vec3(0.0f, -1.0f, 0.0f);
glm::vec3 cube_object_color = glm::vec3(0.6f, 0.3f, 0.0f);
glm::vec3 cube_lighting_pos = glm::vec3(0.7f, 0.0f, 0.0f);
glm::vec3 cube_lighting_color = glm::vec3(1.0f, 1.0f, 1.0f);


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
    
    
    // generate buffers
    GLuint vbo, vao;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    
    // load the buffer data
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    /* ====================================================== */
    
    
    /* ============= Assigning Vertex Attributes ============ */
    glBindVertexArray(vao);
    const size_t stride = 6 * sizeof(float);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*) 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, ((void*)(3 * sizeof(float))));
    glEnableVertexAttribArray(1);    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
    /* ====================================================== */
    
    
    /* ============= Shader gen, compiling, and linking  ============ */
    GLuint vs, fsLight, fsObject, prgObject, prgLight;
    vs = createShader("shaders/vertex.glsl", GL_VERTEX_SHADER);
    fsLight = createShader("shaders/light-fragment.glsl", GL_FRAGMENT_SHADER);
    fsObject = createShader("shaders/object-fragment.glsl", GL_FRAGMENT_SHADER);
    
    int success, length;
    char infolog[512];
    
    prgLight = linkShaders(vs, fsLight);
    prgObject = linkShaders(vs, fsObject);
    glDeleteShader(vs);
    glDeleteShader(fsObject);
    glDeleteShader(fsLight);
    /* ====================================================== */


    
    /* ============= Setting uniform variables ============ */

    glUseProgram(prgObject);
    glUniform3f(glGetUniformLocation(prgObject, "light_color"), cube_lighting_color.x, cube_lighting_color.y, cube_lighting_color.z);
    glUniform3f(glGetUniformLocation(prgObject, "surface_color"), cube_object_color.x, cube_object_color.y, cube_object_color.z);
    glUseProgram(0);
    
    glUseProgram(prgLight);
    glUniform3f(glGetUniformLocation(prgLight, "surface_color"), cube_lighting_color.x, cube_lighting_color.y, cube_lighting_color.z);
    glUseProgram(0);
    
    /* ====================================================== */
    
    
    // main loop
    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glfwPollEvents();
        
        // Calculate tranformation matrices
        glBindVertexArray(vao);
        model_object = glm::mat4(1.0f);
        model_object = glm::translate(model_object, cube_object_pos);
        model_object = glm::scale(model_object, glm::vec3(1.0f, 1.0f, 1.0f));
        model_lighting = glm::mat4(1.0f);
        model_lighting = glm::rotate(model_lighting, (float) glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        model_lighting = glm::translate(model_lighting, cube_lighting_pos);
        model_lighting = glm::scale(model_lighting, glm::vec3(0.10f));
        view = cam.getViewMatrix();
        projection = glm::perspective(cam.getFov(), width / height, 0.1f, 100.0f);
        // glUniformMatrix4fv(glGetUniformLocation(prgObject, "view"), 1, GL_FALSE, glm::value_ptr(view));
        // glUniformMatrix4fv(glGetUniformLocation(prgObject, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        
        // Draw cube object
        glUseProgram(prgObject);
        glUniformMatrix4fv(glGetUniformLocation(prgObject, "model"), 1, GL_FALSE, glm::value_ptr(model_object));
        glUniformMatrix4fv(glGetUniformLocation(prgObject, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(prgObject, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glm::vec3 light_pos = glm::vec3(model_lighting * glm::vec4(cube_lighting_pos, 1.0f));
        glUniform3f(glGetUniformLocation(prgObject, "light_pos"), light_pos.x, light_pos.y, light_pos.z);
        glUniform3f(glGetUniformLocation(prgObject, "viewer_pos"), cam.getPosition().x, cam.getPosition().y, cam.getPosition().z);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        
        // Draw cube lighting
        glUseProgram(prgLight);
        glUniformMatrix4fv(glGetUniformLocation(prgObject, "model"), 1, GL_FALSE, glm::value_ptr(model_lighting));
        glUniformMatrix4fv(glGetUniformLocation(prgObject, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(prgObject, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glDrawArrays(GL_TRIANGLES, 0, 36);


        glfwSwapBuffers(window);
    }

    // clear and return
    glfwTerminate();

    return 0;
}