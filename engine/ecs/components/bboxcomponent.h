#pragma once

#include <glm/glm.hpp>

#include "ecs/icomponent.h"

struct BBoxComponent : public ecs::IComponent<BBoxComponent>
{
    glm::vec3 min {0};
    glm::vec3 max {0};
};
