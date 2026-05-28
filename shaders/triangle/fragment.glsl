#version 420 core

in vec2 out_tex;

out vec4 FragColor;

uniform sampler2D container;
uniform sampler2D smiley;
uniform vec3 color;

void main() {
    // FragColor = mix(texture(container, out_tex), texture(smiley, out_tex), 0.3);
    FragColor = vec4(color, 1.0f);
}