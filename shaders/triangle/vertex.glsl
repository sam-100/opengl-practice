#version 420 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 tex_coords;

out vec4 out_color;
out vec2 out_tex;

uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(pos.x, pos.y, pos.z, 1.0);
    out_color = color;
    out_tex = tex_coords;
}