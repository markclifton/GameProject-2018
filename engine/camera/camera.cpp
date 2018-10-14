#include "camera.h"

#include <math.h>

void Camera::Update() {
    //
    projection = glm::perspective(field_of_view, aspect, static_cast<double>(m_clippingPlanes.x), static_cast<double>(m_clippingPlanes.y));

    camera_direction = glm::normalize(camera_look_at - camera_position);

    // Calculate Quat for Pitch and Heading
    glm::quat pitch_quat = glm::angleAxis(camera_pitch, glm::cross(camera_direction, camera_up));
    glm::quat heading_quat = glm::angleAxis(camera_heading, camera_up);

    // Get New Camera Direction based on heading and pitch
    camera_direction = glm::rotate(glm::normalize(glm::cross(pitch_quat, heading_quat)), camera_direction);

    camera_position += camera_position_delta;
    camera_look_at = camera_position + camera_direction;

    // Smoothing motion to a stop
    camera_heading *= .5;
    camera_pitch *= .5;
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
