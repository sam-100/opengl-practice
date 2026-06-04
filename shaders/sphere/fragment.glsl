#version 420 core

in vec3 FragPos;
out vec4 FragColor;

uniform vec3 surface_color;
uniform vec3 viewer_pos;
uniform vec3 center_pos;

const float ambient_strength = 0.2f;
const float specular_strength = 0.7f;
const float shininess = 32.0f;
const vec3 light_dir = normalize(vec3(0.0f, -1.0f, -1.0f));
vec3 light_color;

void main() {
    light_color = vec3(1.0f, 1.0f, 1.0f);
    vec3 ambient = light_color * ambient_strength;

    vec3 normal = normalize(FragPos - center_pos);
    float diffuse_component = max(dot(normal, -light_dir), 0.0f);
    vec3 diffuse = diffuse_component * light_color;

    vec3 viewer_dir = normalize(viewer_pos - FragPos);
    vec3 reflect_dir = normalize(reflect(light_dir, normal));
    float specular_component = pow(max(dot(viewer_dir, reflect_dir), 0.0f), shininess);
    vec3 specular = specular_component * specular_strength * light_color;
    
    FragColor = vec4((ambient + diffuse + specular) * surface_color, 1.0f);
}