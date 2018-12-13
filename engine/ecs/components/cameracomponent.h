#pragma once

#include "ecs/icomponent.h"

#include "camera/camera.h"

struct CameraComponent : public ecs::IComponent<CameraComponent>
{
    Camera3D camera;
};
