#version 420 core

in vec4 out_color;
in vec2 out_tex;

out vec4 FragColor;

uniform sampler2D container;


void main() {
    FragColor = texture(container, out_tex);
}