#pragma once

#include "glad/gl.h"
#include <glm/vec3.hpp>

#include "drawablebasics.h"
#include "drawableobject.h"

namespace drawable
{
class Triangle : public DrawableObject
{
public:
    Triangle(glm::vec3 center, Shader* shader);
    void draw(glm::mat4 transform = glm::mat4(1.f)) override;
};
}
