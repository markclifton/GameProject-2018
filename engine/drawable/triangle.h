#pragma once

#include "glad/gl.h"
#include <glm/vec3.hpp>

#include "drawableobject.h"

namespace drawable
{
class Triangle : public DrawableObject
{
public:
    Triangle(glm::vec3 center, Shader* shader);
};
}
