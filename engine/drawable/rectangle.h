#pragma once

#include "drawableobject.h"

namespace drawable
{
class Rectangle : public DrawableObject
{
public:
    Rectangle(glm::vec3 center, Shader* shader);
};
}
