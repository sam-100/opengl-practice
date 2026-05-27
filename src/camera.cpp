#include "camera.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>
#include "utils.hpp"

using namespace std;

camera::camera(glm::vec3 position, glm::vec3 front, glm::vec3 right, float fov) {
    m_position = position;
    m_front = front;
    m_right = right;
    m_fov = fov;
}


glm::mat4 camera::getViewMatrix() const {
    glm::vec3 up = glm::normalize(glm::cross(m_right, m_front));
    return glm::lookAt(m_position, m_position + m_front, up);
}


void camera::move_front(float distance) {
    m_position += m_front * distance;
}

void camera::move_right(float distance) {
    m_position += m_right * distance;
}

void camera::turn_yaw(float angle) {
    glm::vec3 up = glm::normalize(glm::cross(m_right, m_front));
    glm::mat4 rotation_mat = glm::rotate(glm::mat4(1.0f), angle, up);
    m_front = glm::vec3(rotation_mat * glm::vec4(m_front, 0.0f));
    m_front = glm::normalize(m_front);
    m_right = glm::vec3(rotation_mat * glm::vec4(m_right, 0.0f));
    m_right = glm::normalize(m_right);
}

void camera::turn_pitch(float angle) {
    glm::mat4 rotation_mat = glm::rotate(glm::mat4(1.0f), angle, m_right);
    m_front = glm::vec3(rotation_mat * glm::vec4(m_front, 0.0f));
    m_front = glm::normalize(m_front);
}

void camera::turn_roll(float angle) {
    // todo: to be implemented
}

void camera::print() const {
    cout << "camera attributes: " << endl;
    cout << "\tposition: " << m_position << endl;
    cout << "\tfront: " << m_front << endl;
    cout << "\tright: " << m_right << endl;
    cout << "\tdot product between front and right direction = " << glm::dot(m_front, m_right) << endl;
    cout << "\tlength of front = " << glm::length(m_front) << endl;
    cout << "\tlength of right = " << glm::length(m_right) << endl;
}

