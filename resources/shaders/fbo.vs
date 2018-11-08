#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 uv;

out FSData {
    vec4 color;
    vec3 uv;
} fs;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(position, 1);

    fs.color = color;
    fs.uv = uv;
}
