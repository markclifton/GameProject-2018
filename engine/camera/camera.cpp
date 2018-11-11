#include "camera.h"

#include <GLFW/glfw3.h>

void Camera3D::Update(bool force) {
    if(!force)
    {
        if(m_timer.get()*1000 < (1000/60.))
        {
            return;
        }
        else
        {
            m_speedModifier = m_timer.reset()*1000 / (1000/60.);
        }
    }

    m_projection = glm::perspective(m_fov, m_aspect, static_cast<double>(m_clippingPlanes.x), static_cast<double>(m_clippingPlanes.y));

    // Calculate XYZ movement delta
    m_cameraPositionDelta = m_cameraDirection * m_cameraInputDelta.z;
    m_cameraPositionDelta -= glm::cross(m_cameraDirection, m_cameraUp) * m_cameraInputDelta.x;
    m_cameraPositionDelta += m_cameraUp * m_cameraInputDelta.y;

    // Ensure XYZ movement doesn't exceed movement speed
    if( glm::length(m_cameraPositionDelta) > 0 )
    {
        m_cameraPositionDelta = glm::normalize(m_cameraPositionDelta);
    }
    m_cameraPositionDelta *= m_movementSpeed * static_cast<float>(m_speedModifier);

    m_cameraDirection = glm::normalize(m_cameraLookAt - m_cameraPosition);

    // Calculate Quat for Pitch and Heading
    glm::quat pitch_quat = glm::angleAxis(m_cameraPitch, glm::cross(m_cameraDirection, m_cameraUp));
    glm::quat heading_quat = glm::angleAxis(m_cameraHeading, m_cameraUp);

    // Get New Camera Direction based on heading and pitch
    m_cameraDirection = glm::rotate(glm::normalize(glm::cross(pitch_quat, heading_quat)), m_cameraDirection);

    m_cameraPosition += m_cameraPositionDelta;
    m_cameraLookAt = m_cameraPosition + m_cameraDirection;

    m_view = glm::lookAt(m_cameraPosition, m_cameraLookAt, m_cameraUp);
}

void Camera3D::SetFOV(double fov) {
    m_fov = fov;
}

void Camera3D::SetViewport(int loc_x, int loc_y, int width, int height) {
    m_viewportX = loc_x;
    m_viewportY = loc_y;
    m_windowWidth = width;
    m_windowHeight = height;
    m_aspect = width / double(height);
}

void Camera3D::SetClipping(float near_clip_distance, float far_clip_distance) {
    m_clippingPlanes.x = near_clip_distance;
    m_clippingPlanes.y = far_clip_distance;
}

void Camera3D::ChangePitch(float radians) {
    m_cameraPitch = fmod(m_cameraPitch + radians, static_cast<float>(2 * 3.141592653589793238));
}

void Camera3D::ChangeHeading(float radians) {
    m_cameraHeading = fmod(m_cameraHeading + radians, static_cast<float>(2 * 3.141592653589793238));
}

void Camera3D::GetMatricies(glm::mat4 &P, glm::mat4 &V) {
    P = m_projection;
    V = m_view;
}

void Camera3D::process(int key, int /*scancode*/, int action, int /*mods*/)
{
    switch (key)
    {
    case GLFW_KEY_W:
        if(action == GLFW_PRESS)
        {
            m_cameraInputDelta.z += m_movementSpeed;
        }
        else if(action == GLFW_RELEASE)
        {
            m_cameraInputDelta.z -= m_movementSpeed;
        }
        break;
    case GLFW_KEY_S:
        if(action == GLFW_PRESS)
        {
            m_cameraInputDelta.z -= m_movementSpeed;
        }
        else if(action == GLFW_RELEASE)
        {
            m_cameraInputDelta.z += m_movementSpeed;
        }
        break;
    case GLFW_KEY_A:
        if(action == GLFW_PRESS)
        {
            m_cameraInputDelta.x += m_movementSpeed;
        }
        else if(action == GLFW_RELEASE)
        {
            m_cameraInputDelta.x -= m_movementSpeed;
        }
        break;
    case GLFW_KEY_D:
        if(action == GLFW_PRESS)
        {
            m_cameraInputDelta.x -= m_movementSpeed;
        }
        else if(action == GLFW_RELEASE)
        {
            m_cameraInputDelta.x += m_movementSpeed;
        }
        break;
    case GLFW_KEY_E:
        if(action == GLFW_PRESS)
        {
            m_cameraInputDelta.y += m_movementSpeed;
        }
        else if(action == GLFW_RELEASE)
        {
            m_cameraInputDelta.y -= m_movementSpeed;
        }
        break;
    case GLFW_KEY_Q:
        if(action == GLFW_PRESS)
        {
            m_cameraInputDelta.y -= m_movementSpeed;
        }
        else if(action == GLFW_RELEASE)
        {
            m_cameraInputDelta.y += m_movementSpeed;
        }
        break;
    case GLFW_KEY_UP:
        if(action == GLFW_PRESS)
        {
            ChangePitch(m_rotationSpeed);
        }
        else if(action == GLFW_RELEASE)
        {
            ChangePitch(-m_rotationSpeed);
        }
        break;
    case GLFW_KEY_DOWN:
        if(action == GLFW_PRESS)
        {
            ChangePitch(-m_rotationSpeed);
        }
        else if(action == GLFW_RELEASE)
        {
            ChangePitch(m_rotationSpeed);
        }
        break;
    case GLFW_KEY_LEFT:
        if(action == GLFW_PRESS)
        {
            ChangeHeading(m_rotationSpeed);
        }
        else if(action == GLFW_RELEASE)
        {
            ChangeHeading(-m_rotationSpeed);
        }
        break;
    case GLFW_KEY_RIGHT:
        if(action == GLFW_PRESS)
        {
            ChangeHeading(-m_rotationSpeed);
        }
        else if(action == GLFW_RELEASE)
        {
            ChangeHeading(m_rotationSpeed);
        }
        break;
    }
}

