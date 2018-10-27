#version 450 core

out vec4 finalColor;

in vec4 fs_color;
in vec3 fs_uv;

in vec3 pos_w;
in vec3 normal_c;
in vec3 eye_c;
in vec3 light_c;
in vec3 light_w;

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

    if(normal_c.x == 0 && normal_c.y == 0 && normal_c.z == 0)
    {
        return;
    }

    vec3 LightColor = vec3(1,1,1);
    float LightPower = 50.0f;

    // Material properties
    vec3 MaterialDiffuseColor = finalColor.rgb;
    vec3 MaterialAmbientColor = vec3(0.1,0.1,0.1) * MaterialDiffuseColor;
    vec3 MaterialSpecularColor = vec3(0.3,0.3,0.3);

    float distance = length( light_w - pos_w );

    vec3 n = normalize( normal_c );
    vec3 l = normalize( light_c );
    float cosTheta = clamp( dot( n,l ), 0,1 );

    vec3 E = normalize(eye_c);
    vec3 R = reflect(-l,n);
    float cosAlpha = clamp( dot( E,R ), 0,1 );

    finalColor = vec4(
            MaterialAmbientColor +
            MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance*distance) +
            MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,5) / (distance*distance), finalColor.a);
}
