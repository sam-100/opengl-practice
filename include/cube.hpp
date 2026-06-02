#ifndef CUBE_HPP
#define CUBE_HPP

#include "object.hpp"
#include "glm/glm.hpp"

class cube : public object {
private:
    float m_side;
    glm::vec3 m_color;

public:
    cube(float side, float mass, glm::vec3 position, glm::vec3 velocity, glm::vec3 color);
    void render(const glm::mat4 &view, const glm::mat4 &projection, glm::vec3 cam_position) const;
};

#endif