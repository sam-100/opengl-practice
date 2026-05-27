#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class camera {
private:
    glm::vec3 m_position, m_front, m_right;
    float fov;  // in radians

public:
    camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f), ) {
        
    }


};

#endif