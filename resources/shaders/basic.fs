#version 450 core

out vec4 finalColor;

in vec4 fs_color;
in vec3 fs_uv;
in vec4 fs_position;
in vec4 fs_camera;

uniform sampler2D myTextures[16];

void main()
{
    if( fs_uv.z < 0.f )
    {
        finalColor = fs_color;
    }   
    else
    {
        finalColor = texture2D(myTextures[int(fs_uv.z - .5)], fs_uv.xy);
    }
}
