#version 450 core

out vec4 finalColor;

in FSData {
    vec4 color;
    vec3 uv;
} fs;

uniform sampler2D textures[16];

void main()
{
    finalColor = fs.color;
    if( fs.uv.z >= 0.f )
    {
        finalColor = texture2D(textures[int(fs.uv.z - .5)], fs.uv.xy);
    }
}
