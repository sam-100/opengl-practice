#version 420 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex_coords;

uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(pos.x, pos.y, pos.z, 1.0);
}