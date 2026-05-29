#version 420 core

out vec4 FragColor;

uniform vec3 color;
uniform vec3 light_color;

void main() {
    float ambient_strength = 0.2f;
    FragColor = vec4(color * light_color * ambient_strength, 1.0f);
}