#pragma once

#include "glm/matrix.hpp"

#include <algorithm>
#include <iostream>

#include "drawable/drawableobject.h"
#include "ecs/isystem.h"

namespace ecs
{

class BatchRenderingSystem : public ISystem
{
public:
    BatchRenderingSystem()
    {

    }

    void update(std::vector<COMP_TYPE> componentsToUse, float, void** component) override
    {



    }
};

}
