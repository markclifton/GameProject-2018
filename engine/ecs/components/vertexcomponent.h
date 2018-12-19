#pragma once

#include "ecs/icomponent.h"

#include "glm/vec3.hpp"
#include "glm/matrix.hpp"

namespace ps
{
struct VertexComponent : public ecs::IComponent<VertexComponent>
{
    glm::vec4 color{1,1,1,1};
    glm::vec3 pos{0,0,0};
    glm::vec3 uv{0,0,-1};
    glm::vec3 normal{0,0,0};
    glm::mat4 model{1.0f};
};
}
