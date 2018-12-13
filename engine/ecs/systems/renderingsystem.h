#pragma once

#include "ecs/components/vertexcomponent.h"
#include "ecs/isystem.h"

namespace ecs
{

class RendererSystem : public ISystem
{
public:
    RendererSystem();
    void update(std::vector<COMP_TYPE> componentsToUse, float, void** component) override;
};

}
