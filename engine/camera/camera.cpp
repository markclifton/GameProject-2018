#include "camera.h"

#include <GLFW/glfw3.h>

#include <math.h>

void Camera::Update() {
    projection = glm::perspective(field_of_view, aspect, static_cast<double>(m_clippingPlanes.x), static_cast<double>(m_clippingPlanes.y));

    camera_direction = glm::normalize(camera_look_at - camera_position);

    // Calculate Quat for Pitch and Heading
    glm::quat pitch_quat = glm::angleAxis(camera_pitch, glm::cross(camera_direction, camera_up));
    glm::quat heading_quat = glm::angleAxis(camera_heading, camera_up);

    // Get New Camera Direction based on heading and pitch
    camera_direction = glm::rotate(glm::normalize(glm::cross(pitch_quat, heading_quat)), camera_direction);

    camera_position += camera_position_delta;
    camera_look_at = camera_position + camera_direction;

    // Stop all camera motion after updating
    camera_heading *= .5f;
    camera_pitch *= .5f;
    camera_position_delta = camera_position_delta * .5f;

    view = glm::lookAt(camera_position, camera_look_at, camera_up);
}

void Camera::SetFOV(double fov) {
    field_of_view = fov;
}

void Camera::SetViewport(int loc_x, int loc_y, int width, int height) {
    viewport_x = loc_x;
    viewport_y = loc_y;
    window_width = width;
    window_height = height;
    aspect = width / double(height);
}

void Camera::SetClipping(float near_clip_distance, float far_clip_distance) {
    m_clippingPlanes.x = near_clip_distance;
    m_clippingPlanes.y = far_clip_distance;
}

void Camera::ChangePitch(float degrees) {
    camera_pitch = fmod(camera_pitch + degrees,360.f);
}

void Camera::ChangeHeading(float degrees) {
    camera_heading = fmod(camera_heading + degrees,360.f);
}

void Camera::GetMatricies(glm::mat4 &P, glm::mat4 &V) {
    P = projection;
    V = view;
}

void Camera::process(int key, int scancode, int action, int mods)
{
    switch (key)
    {
    case GLFW_KEY_W:
        camera_position_delta += camera_direction * .01f;
        break;
    case GLFW_KEY_S:
        camera_position_delta -= camera_direction * .01f;
        break;
    case GLFW_KEY_A:
        camera_position_delta -= glm::cross(camera_direction, camera_up) * .01f;
        break;
    case GLFW_KEY_D:
        camera_position_delta += glm::cross(camera_direction, camera_up) * .01f;
        break;
    case GLFW_KEY_E:
        camera_position_delta += camera_up * .01f;
        break;
    case GLFW_KEY_Q:
        camera_position_delta -= camera_up * .01f;
        break;
    case GLFW_KEY_UP:
        ChangePitch(.01f);
        break;
    case GLFW_KEY_DOWN:
        ChangePitch(-.01f);
        break;
    case GLFW_KEY_LEFT:
        ChangeHeading(-.01f);
        break;
    case GLFW_KEY_RIGHT:
        ChangeHeading(.01f);
        break;
    }
}

