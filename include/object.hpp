#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "glm/glm.hpp"
#include "GL/gl.h"

class object {
private:
    float m_mass;
    glm::vec3 m_position, m_velocity;
    GLuint vao, prg;

public:
    object(float mass, glm::vec3 position, glm::vec3 velocity);
    void update(float dt);
    void applyForce(glm::vec3 force, float dt);
    virtual void render() const = 0;
};

#endif

