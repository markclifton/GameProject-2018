#pragma once

#include "glm/matrix.hpp"

#include <algorithm>
#include <iostream>

#include "drawable/drawableobject.h"
#include "ecs/components/vertexcomponent.h"
#include "ecs/isystem.h"
#include "shaders/shader.h"

namespace ecs
{

class RendererSystem : public ISystem
{
public:
    RendererSystem();
    void update(std::vector<COMP_TYPE> componentsToUse, float, void** component) override;
};

}
