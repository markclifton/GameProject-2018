#pragma once

#include "ps/glad/gl.h"
#include "glm/vec3.hpp"

#include "ps/ecs/entities/drawableentity.h"

namespace ps
{
namespace drawable
{
class Triangle : public DrawableEntity
{
public:
    Triangle(const std::string& context, glm::vec3 center, Shader* shader);
};
}
}
