#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 uv;
layout (location = 3) in vec3 normal;
layout (location = 4) in mat4 model;

out FSData {
    vec4 color;
    vec3 uv;
    float distance_w;
    vec3 pos_c;
    vec3 normal_c;
} fs;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 transform;
uniform vec4 camera;

void main()
{
    gl_Position = projection * view * transform * model * vec4(position, 1);

    fs.pos_c = ( view * transform * model * vec4(position,1)).xyz;
    fs.normal_c = ( view * transform * model * vec4(normal,0)).xyz;

    fs.color = color;
    fs.uv = uv;

    fs.distance_w = length(camera.xyz - (transform * model * vec4(position, 1)).xyz);
}
