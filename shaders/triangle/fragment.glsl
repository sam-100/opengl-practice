#version 420 core

in vec4 out_color;
in vec2 out_tex;

out vec4 FragColor;

uniform sampler2D container;
uniform sampler2D smiley;

void main() {
    FragColor = mix(texture(container, out_tex), texture(smiley, out_tex), 0.3);
}