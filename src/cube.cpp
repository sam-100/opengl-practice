#include "glad/glad.h"
#include "cube.hpp"
#include "utils.hpp"
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_access.hpp"
#include "glm/gtc/type_ptr.hpp"

static float vertices[] = {
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


cube::cube(float side, float mass, glm::vec3 position, glm::vec3 velocity, glm::vec3 color) : object(mass, position, velocity) {
    m_side = side;
    m_color = color;

    // generate buffers
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &m_vao);

    
    // load the buffer data
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    /* ============= Assigning Vertex Attribtes ============ */
    glBindVertexArray(m_vao);
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
    const char *vs_path = "shaders/cube/vertex.glsl", *fs_path = "shaders/cube/fragment.glsl";
    GLuint vs, fs;
    vs = createShader(vs_path, GL_VERTEX_SHADER);
    fs = createShader(fs_path, GL_FRAGMENT_SHADER);
    
    int success, length;
    char infolog[512];
    
    m_prg = linkShaders(vs, fs);
    glDeleteShader(vs);
    glDeleteShader(fs);
    /* ====================================================== */



    /* ============= Setting uniform variables ============ */
    glUseProgram(m_prg);
    glUniform3f(glGetUniformLocation(m_prg, "surface_color"), m_color.x, m_color.y, m_color.z);
    glUseProgram(0);
    /* ====================================================== */
}

void cube::render(const glm::mat4 &view, const glm::mat4 &projection, glm::vec3 cam_position) const {
    glBindVertexArray(m_vao);
    glUseProgram(m_prg);

    glm::mat4 model(1.0f);
    model = glm::translate(model, m_position);
    model = glm::scale(model, glm::vec3(m_side));
    glUniformMatrix4fv(glGetUniformLocation(m_prg, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(m_prg, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(m_prg, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniform3f(glGetUniformLocation(m_prg, "viewer_pos"), cam_position.x, cam_position.y, cam_position.z);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glUseProgram(0);
    glBindVertexArray(0);
}
