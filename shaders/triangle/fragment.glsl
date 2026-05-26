#version 420 core

in vec4 out_color;
in vec2 out_tex;

out vec4 FragColor;

uniform sampler2D ourTexture;


void main() {
    FragColor = texture(ourTexture, out_tex);
}