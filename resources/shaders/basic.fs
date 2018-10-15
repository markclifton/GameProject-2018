#version 450 core

out vec4 finalColor;

in vec4 fs_color;
in vec3 fs_uv;

uniform sampler2D myTexture;

void main()
{
    if( fs_uv.z != 0.f )    
    {
        finalColor = texture2D(myTexture, fs_uv.xy);
    }   
    else
    {
        finalColor = fs_color;
    }
}
