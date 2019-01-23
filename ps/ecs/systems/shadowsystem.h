#pragma once

#include "ps/ecs/isystem.h"

namespace ps
{
namespace ecs
{
class ShadowSystem : public ISystem
{
public:
    ShadowSystem();
    void update(std::vector<COMP_TYPE> componentsToUse, float, void* component) override;
};
}
}
