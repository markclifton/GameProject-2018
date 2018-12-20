#pragma once

#include <glm/vec3.hpp>

#include "ps/ecs/entities/drawableentity.h"

namespace ps
{
namespace drawable
{
class Rectangle : public DrawableEntity
{
public:
    Rectangle(const std::string& context, glm::vec3 center, Shader* shader);
};
}
}
