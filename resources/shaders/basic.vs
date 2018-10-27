#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 uv;
layout (location = 3) in vec3 normal;
layout (location = 4) in mat4 model;

out vec4 fs_color;
out vec3 fs_uv;

out vec3 pos_w;
out vec3 normal_c;
out vec3 eye_c;
out vec3 light_c;
out vec3 light_w;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 transform;
uniform vec4 camera;

void main()
{
    gl_Position = projection * view * transform * model * vec4(position, 1);

    pos_w = (transform * model * vec4(position, 1)).xyz;

    vec3 pos_c = ( view * transform * model * vec4(position,1)).xyz;
    eye_c = vec3(0,0,0) - pos_c;

    vec3 LightPosition_cameraspace = ( view * camera).xyz;
    light_c = LightPosition_cameraspace + eye_c;

    normal_c = ( view * transform * model * vec4(normal,0)).xyz;

    fs_color = color;
    fs_uv = uv;

    light_w = camera.xyz;
}
