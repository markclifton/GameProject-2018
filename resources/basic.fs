#version 450 core
in vec3 fs_color;
out vec4 finalColor;

void main()
{
    finalColor = vec4(fs_color, 1);
}
