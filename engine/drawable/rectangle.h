#pragma once

#include "ecs/entities/drawableentity.h"

namespace drawable
{
class Rectangle : public DrawableEntity
{
public:
    Rectangle(glm::vec3 center, Shader* shader);
};
}
