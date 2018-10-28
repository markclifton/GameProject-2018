#version 450 core

out vec4 finalColor;

in FSData {
    vec4 color;
    vec3 uv;
    float distance_w;
    vec3 pos_c;
    vec3 normal_c;
} fs;

uniform sampler2D textures[16];

struct Light
{
    vec3 color;
    float intensity;
};

vec4 calculateLight( Light light, vec3 normal, vec3 direction, float distance )
{
    vec3 n = normalize( normal );
    vec3 l = normalize( direction );
    vec3 r = reflect(-l,n);

    float cosTheta = clamp( dot( normal,l ), 0,1 );
    float cosAlpha = clamp( dot( l,r ), 0,1 );

    return vec4( light.color * cosTheta / (distance*distance)
               + light.color * pow(cosAlpha,5) / (distance*distance), 1.f )
               * light.intensity ;
}

void main()
{
    finalColor = fs.color;
    if( fs.uv.z >= 0.f )
    {
        finalColor = texture2D(textures[int(fs.uv.z - .5)], fs.uv.xy);
    }

    if(length(fs.normal_c) > 0)
    {
        Light light;
        light.color = vec3(1,1,1);
        light.intensity = 50.f;

        float alpha = finalColor.a;
        finalColor *= .1;
        finalColor += calculateLight( light, fs.normal_c, -fs.pos_c, fs.distance_w ) * finalColor;
        finalColor.a = alpha;
    }
}
