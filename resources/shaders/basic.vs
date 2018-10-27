#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 uv;
layout (location = 3) in mat4 model;

out vec4 fs_color;
out vec3 fs_uv;
out vec4 fs_position;
out vec4 fs_camera;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 transform;
uniform vec4 camera;

void main()
{
    gl_Position = projection * view * transform * model * vec4(position, 1);

    fs_color = color;
    fs_uv = uv;
    fs_position = gl_Position;
    fs_camera = camera;
}
