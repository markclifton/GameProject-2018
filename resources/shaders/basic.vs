#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 uv;

out vec4 fs_color;
out vec3 fs_uv;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model = mat4(1.0);

void main()
{
    gl_Position = projection * view * model * vec4(position, 1);

    fs_color = color;
    fs_uv = uv;
}
