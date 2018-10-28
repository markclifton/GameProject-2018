#version 450 core

out vec4 finalColor;

in FSData {
    vec4 color;
    vec3 uv;
    float distance_w;
    vec3 pos_w;
    vec3 pos_c;
    vec3 normal_c;
} fs;

in mat4 tform;

uniform sampler2D textures[16];

struct Light
{
    vec3 color;
    float intensity;
};

struct PLight
{
    Light light;
    float e;
    float l;
    float c;
    vec3 pos_w;
};

vec4 calculateLight( Light light, vec3 normal, vec3 direction, float distance )
{
    vec3 n = normalize( normal );
    vec3 l = normalize( direction );
    vec3 r = reflect(-l,n);

    float totalColor = 0;

    float diffuseFactor = clamp( dot( normal,l ), 0,1 ) / (distance*distance);
    if(diffuseFactor > 0)
    {
        totalColor += diffuseFactor;

        float cosAlpha = clamp( dot( l,r ), 0,1 );
        float specularFactor = pow(cosAlpha,5) / (distance*distance);
        if( specularFactor > 0)
        {
            totalColor += specularFactor;
        }
    }

    return vec4( light.color * totalColor, 1.f ) * light.intensity;
}

vec4 calculatePLight(PLight plight, vec3 normal)
{
    vec3 direction = fs.pos_w - plight.pos_w;
    float distance = length(direction);

    vec4 color = calculateLight(plight.light, normal, -direction, distance);

    plight.c += 0.0001;
    float attenuation = (plight.e * distance * distance) + (plight.l * distance) + plight.c;
    return color / attenuation;
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
        light.intensity = 5.f;

        PLight plight;
        plight.light.color = vec3(1,1,1);
        plight.light.intensity = 100.f;
        plight.pos_w = (tform * vec4(-1,0,-5,1)).xyz;
        plight.e = 1;
        plight.l = 0;
        plight.c = 0;

        vec4 totalLight = vec4(.1,.1,.1,1);
        totalLight += calculateLight( light, fs.normal_c, -fs.pos_c, fs.distance_w );
        totalLight += calculatePLight(plight, fs.normal_c);

        float alpha = finalColor.a;
        finalColor *= totalLight;
        finalColor.a = alpha;
    }
}
