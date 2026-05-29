#version 420 core

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;


uniform vec3 surface_color;
uniform vec3 light_color;
uniform vec3 light_pos;

void main() {
    float ambient_strength = 0.2f;

    vec3 ambient = light_color * ambient_strength;
    vec3 light_dir = normalize(light_pos - FragPos);
    float diff_component = max(dot(Normal, light_dir), 0.0f);
    vec3 diffuse = diff_component * light_color;

    FragColor = vec4((ambient + diffuse) * surface_color, 1.0f);
}