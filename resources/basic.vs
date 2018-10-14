#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 fs_color;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    vec4 pos = projection * view * /*model*/ vec4(position, 1.0);
    gl_Position = pos.xyzw;
    fs_color = color;
}
