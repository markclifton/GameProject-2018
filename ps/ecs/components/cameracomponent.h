#pragma once

#include "ps/ecs/icomponent.h"
#include "ps/camera/camera.h"

namespace ps
{
struct CameraComponent : public ecs::IComponent<CameraComponent>
{
    Camera3D* camera;
};
}
