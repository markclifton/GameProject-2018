#pragma once

#include "ecs/icomponent.h"
#include "camera/camera.h"

namespace ps
{
struct CameraComponent : public ecs::IComponent<CameraComponent>
{
    Camera3D* camera;
};
}
