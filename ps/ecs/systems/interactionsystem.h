#pragma once

#include "ps/ecs/isystem.h"

namespace ps
{
namespace ecs
{
class InteractionSystem : public ISystem
{
public:
    InteractionSystem();
    void update(std::vector<COMP_TYPE> componentsToUse, float, void** component) override;
};
}
}
