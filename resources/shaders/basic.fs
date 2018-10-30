#version 450 core

out vec4 finalColor;

in FSData {
    vec3 pos;
    vec4 color;
    vec3 uv;
    vec3 normal;
    float distance;
} fs;

in mat4 tform;

uniform sampler2D textures[16];

struct Light
{
    vec3 color;
    float intensity;
};

struct PointLight
{
    Light light;
    float e;
    float l;
    float c;
    vec3 pos_w;
};

struct SpotLight
{
    PointLight light;
    vec3 direction;
    float cutoff;
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

        float specularFactor = clamp( dot( l,r ), 0,1 );
        if( specularFactor > 0)
        {
            totalColor += pow(specularFactor,5) / (distance*distance);
        }
    }

    return vec4( light.color * totalColor, 1.f ) * light.intensity;
}

vec4 calculatePLight(PointLight plight, vec3 normal)
{
    vec3 direction = fs.pos - plight.pos_w;
    float distance = length(direction);

    vec4 color = calculateLight(plight.light, normal, -direction, distance);

    plight.c += 0.0001;
    float attenuation = (plight.e * distance * distance) + (plight.l * distance) + plight.c;
    return color / attenuation;
}

vec4 calculateSpotLight(SpotLight slight, vec3 normal)
{
    vec3 direction = normalize(fs.pos - slight.light.pos_w);
    float spotFactor = dot(direction, slight.direction);

    vec4 color = vec4(0,0,0,0);
    if( spotFactor > slight.cutoff)
    {
        color = calculatePLight(slight.light, normal);
        color *= (1.0 - (1.0 - spotFactor) / (1.0 - slight.cutoff));
    }

    return color;
}

void main()
{
    finalColor = fs.color;
    if( fs.uv.z >= 0.f )
    {
        finalColor = texture2D(textures[int(fs.uv.z - .5)], fs.uv.xy);
    }

    if(length(fs.normal) > 0)
    {
        Light light;
        light.color = vec3(1,1,1);
        light.intensity = 5.f;

        PointLight plight;
        plight.light.color = vec3(1,1,1);
        plight.light.intensity = 25.f;
        plight.pos_w = (tform * vec4(-1,0,-5,1)).xyz;
        plight.e = 1;
        plight.l = 0;
        plight.c = 0;

        vec4 totalLight = vec4(.05,.05,.05,1);
        totalLight += calculateLight( light, fs.normal, -fs.pos, fs.distance );
        totalLight += calculatePLight(plight, fs.normal);

        plight.pos_w = (tform * vec4(1,0,-10,1)).xyz;
        plight.light.color = vec3(1,0,1);
        SpotLight s;
        s.light = plight;
        s.cutoff = 0.5f;
        s.direction = (tform * vec4(-1,0,0,0)).xyz;
        totalLight += calculateSpotLight(s, fs.normal);

        float alpha = finalColor.a;
        finalColor *= totalLight;
        finalColor.a = alpha;
    }
}
