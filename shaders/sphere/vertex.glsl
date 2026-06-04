#version 420 core
layout (location = 0) in vec3 pos;

out vec3 FragPos;

uniform mat4 model, view, projection;

void main() {
    gl_Position = projection * view * model * vec4(pos, 1.0);
    FragPos = vec3(model * vec4(pos, 1.0f));
}