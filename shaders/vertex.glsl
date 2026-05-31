#version 420 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 model, view, projection;
uniform mat3 normal_matrix;

void main() {
    gl_Position = projection * view * model * vec4(pos, 1.0);
    Normal = normal_matrix * normal;
    FragPos = vec3(model * vec4(pos, 1.0f));
}