#version 420 core

out vec4 FragColor;

uniform vec3 surface_color;


void main() {
    FragColor = vec4(surface_color, 1.0f);
}