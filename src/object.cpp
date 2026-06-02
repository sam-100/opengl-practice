#include "object.hpp"

object::object(float mass, glm::vec3 position, glm::vec3 velocity) {
    m_mass = mass;
    m_position = position;
    m_velocity = velocity;
}

void object::update(float dt) {
    m_position += m_velocity * dt;
}

void object::applyForce(glm::vec3 force, float dt) {
    glm::vec3 acceleration = force / m_mass;
    m_velocity += acceleration * (float) dt;
}

