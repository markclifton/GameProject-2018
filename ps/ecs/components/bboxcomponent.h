#pragma once

#include <glm/glm.hpp>

#include "ps/ecs/icomponent.h"

namespace ps
{
struct BBoxComponent : public ecs::IComponent<BBoxComponent>
{
    glm::vec3 min {0};
    glm::vec3 max {0};
};
}
