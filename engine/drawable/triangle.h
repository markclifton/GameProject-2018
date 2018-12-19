#pragma once

#include "glad/gl.h"
#include <glm/vec3.hpp>

#include "ecs/entities/drawableentity.h"

namespace ps
{
namespace drawable
{
class Triangle : public DrawableEntity
{
public:
    Triangle(glm::vec3 center, Shader* shader);
};
}
}
