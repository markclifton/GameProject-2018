#pragma once

#include "ps/ecs/components/vertexcomponent.h"
#include "ps/ecs/isystem.h"

namespace ps
{
namespace ecs
{
class RenderingSystem : public ISystem
{
public:
    RenderingSystem();
    void update(std::vector<COMP_TYPE> componentsToUse, float, void* component) override;
};
}
}
