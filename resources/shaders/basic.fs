#version 450 core

out vec4 finalColor;

in vec4 fs_color;
in vec2 fs_uv;

uniform sampler2D myTexture;

void main()
{
    finalColor = texture2D(myTexture, fs_uv);
}
