#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "glm/glm.hpp"
#include "camera.hpp"
#include "glad/glad.h"
#include "GL/gl.h"
#include "object.hpp"

class sphere : public object {
private:
    float m_radius;
    const float res = 100;
    glm::vec3 color;
    int vertex_count;

public:
    sphere(float radius, float mass, glm::vec3 position, glm::vec3 velocity);
    void render(const glm::mat4 &view, const glm::mat4 &projection, glm::vec3 cam_position) const;
};

#endif
