#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glm/glm.hpp"

class camera {
private:
    glm::vec3 m_position, m_front, m_right;
    float m_fov;  // in radians

public:
    camera(
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f), 
        glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f), 
        glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f), 
        float fov = glm::radians(60.0f)
    );
    
    void move_front(float distance);
    void move_right(float distance);
    void turn_yaw(float angle);
    void turn_pitch(float angle);
    void turn_roll(float angle);


    void print() const;
    float getFov() const;
    glm::mat4 getViewMatrix() const;
    glm::vec3 getPosition() const;
};

#endif