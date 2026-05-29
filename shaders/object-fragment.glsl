#version 420 core

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;


uniform vec3 surface_color;
uniform vec3 light_color;
uniform vec3 light_pos;
uniform vec3 viewer_pos;

const float ambient_strength = 0.2f;
const float specular_strength = 1.0f;
const float shinines_value = 32.0f;

void main() {

    vec3 ambient = light_color * ambient_strength;

    vec3 light_dir = normalize(light_pos - FragPos);
    float diff_component = max(dot(Normal, light_dir), 0.0f);
    vec3 diffuse = diff_component * light_color;

    vec3 viewer_dir = normalize(viewer_pos - FragPos);
    vec3 reflect_dir = normalize(reflect(-light_dir, Normal));
    float specular_component = pow(max(dot(reflect_dir, viewer_dir), 0.0f), shinines_value);
    vec3 specular = specular_component * specular_strength * light_color;

    FragColor = vec4((ambient + diffuse + specular) * surface_color, 1.0f);
}