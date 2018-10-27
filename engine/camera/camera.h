#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utils/keyhandler.h"

using namespace utils;
class Camera3D : public KeyHandler
{
public:
    Camera3D() = default;
    virtual ~Camera3D() = default;

    void Reset();
    void Update();

    void ChangePitch(float degrees);
    void ChangeHeading(float degrees);

    void SetFOV(double fov);
    void SetViewport(int loc_x, int loc_y, int width, int height);
    void SetClipping(float near_clip_distance, float far_clip_distance);

    void GetMatricies(glm::mat4 &P, glm::mat4 &V);

    void process(int key, int scancode, int action, int mods) override;

    inline const glm::vec3& GetPosition() { return m_cameraPosition; }
private:
    int m_viewportX;
    int m_viewportY;
    int m_windowWidth;
    int m_windowHeight;
    double m_aspect { 4/3.};
    double m_fov {45};
    glm::vec2 m_clippingPlanes {.01f, 1000};

    glm::mat4 m_projection {1.f};
    glm::mat4 m_view {1.f};

    float m_cameraHeading {0.f};
    float m_cameraPitch {0.f};

    glm::vec3 m_cameraDirection {0,0,0};
    glm::vec3 m_cameraInputDelta {0.f};
    glm::vec3 m_cameraLookAt {0,0,0};
    glm::vec3 m_cameraPosition {0,0,1};
    glm::vec3 m_cameraPositionDelta {0,0,0};
    glm::vec3 m_cameraUp {0,1,0};

    float m_movementSpeed {.085f};
    float m_rotationSpeed {.045f};
};
