#include "sphere.hpp"
#include "utils.hpp"
#include <vector>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "camera.hpp"


extern glm::vec3 light_color;
extern const float width, height;

sphere::sphere(float radius, float mass, glm::vec3 position, glm::vec3 velocity) : object(mass, position, velocity) {
    m_radius = radius;
    m_position = position;
    m_velocity = glm::vec3(0.0f);
    color = glm::vec3(0.2f, 0.7f, 0.0f);

    // generate buffers
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &m_vao);


    // load the buffer data
    /*
        theta is angle in the XY plane in anti-clockwise direction with Z axis pointing outwards
        phi is angle in the XZ plane in clockwise direction with Y axis pointing inwards
    */
    std::vector<float> vertices;
    for(int i=0; i<res; i++) {
        double theta, theta1;
        theta = M_PI * ((double) i / res);
        theta1 = M_PI * ((double) (i+1) / res);

        for(int j=0; j<res; j++) {
            double phi, phi1;
            phi = 2 * M_PI * ((double) j / res);
            phi1 = 2 * M_PI * ((double) (j+1) / res);
            
            glm::vec3 v1, v2, v3, v4, normal;
            v1 = radialToCartesianCoordinates(radius, theta, phi);
            v2 = radialToCartesianCoordinates(radius, theta1, phi);
            v3 = radialToCartesianCoordinates(radius, theta, phi1);
            v4 = radialToCartesianCoordinates(radius, theta1, phi1);
            
            // triangle-1 (v1, v2, v3)
            vertices.insert(vertices.end(), {v1.x, v1.y, v1.z});
            vertices.insert(vertices.end(), {v2.x, v2.y, v2.z});
            vertices.insert(vertices.end(), {v3.x, v3.y, v3.z});
            
            // triangle-2 (v2, v3, v4)
            vertices.insert(vertices.end(), {v2.x, v2.y, v2.z});
            vertices.insert(vertices.end(), {v3.x, v3.y, v3.z});
            vertices.insert(vertices.end(), {v4.x, v4.y, v4.z});
        }
    }
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    vertex_count = vertices.size() / 3;
    /* ====================================================== */

    
    /* ============= Assigning Vertex Attributes ============ */
    glBindVertexArray(m_vao);
    const size_t stride = 3 * sizeof(float);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*) 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
    /* ====================================================== */

    /* ============= Shader gen, compiling, and linking  ============ */
    const char *vs_path = "shaders/sphere/vertex.glsl", *fs_path = "shaders/sphere/fragment.glsl";
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
    glUniform3f(glGetUniformLocation(m_prg, "surface_color"), color.x, color.y, color.z);
    /* ====================================================== */


}


// void sphere::render(const camera &cam) const {
void sphere::render(const glm::mat4 &view, const glm::mat4 &projection, glm::vec3 cam_position) const {
    glBindVertexArray(m_vao);
    glUseProgram(m_prg);

    glm::mat4 model(1.0f);
    model = glm::translate(model, m_position);
    glUniformMatrix4fv(glGetUniformLocation(m_prg, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(m_prg, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(m_prg, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniform3f(glGetUniformLocation(m_prg, "viewer_pos"), cam_position.x, cam_position.y, cam_position.z);
    glUniform3f(glGetUniformLocation(m_prg, "center_pos"), m_position.x, m_position.y, m_position.z);

    // Draw the sphere
    glDrawArrays(GL_TRIANGLES, 0, vertex_count);
}
