#pragma once

#include "ps/ecs/icomponent.h"

#include "glm/vec3.hpp"

namespace ps
{
struct MovementComponent : public ecs::IComponent<MovementComponent>
{
    glm::vec3 speed {glm::vec3(0,0,0)};
};
}
