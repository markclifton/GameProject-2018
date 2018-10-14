#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../utils/keyhandler.h"

using namespace utils;
class Camera : public KeyHandler
{
public:
    Camera() = default;
    virtual ~Camera() = default;

    void Reset();
    void Update();

    void ChangePitch(float degrees);
    void ChangeHeading(float degrees);

    void SetFOV(double fov);
    void SetViewport(int loc_x, int loc_y, int width, int height);
    void SetClipping(float near_clip_distance, float far_clip_distance);

    void GetMatricies(glm::mat4 &P, glm::mat4 &V);

    //TODO: Improve these
    void process(int key, int scancode, int action, int mods) override;

private:
    int viewport_x;
    int viewport_y;

    int window_width;
    int window_height;

    double aspect { 4/3.};
    double field_of_view {45};
    glm::vec2 m_clippingPlanes {.01f, 1000};

    float camera_heading {0.f};
    float camera_pitch {0.f};

    glm::vec3 camera_position {0,0,1};
    glm::vec3 camera_position_delta {0,0,0};
    glm::vec3 camera_look_at {0,0,0};
    glm::vec3 camera_direction {0,0,0};

    glm::vec3 camera_up {0,1,0};
    glm::vec3 mouse_position {0,0,0};

    glm::mat4 projection {1.f};
    glm::mat4 view {1.f};

};
