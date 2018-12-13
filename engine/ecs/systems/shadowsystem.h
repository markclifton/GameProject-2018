#pragma once

#include "ecs/isystem.h"

namespace ecs
{

class ShadowSystem : public ISystem
{
public:
    ShadowSystem();
    void update(std::vector<COMP_TYPE> componentsToUse, float, void** component) override;
};

}
