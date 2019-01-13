#pragma once

#include "ps/ecs/isystem.h"

namespace ps
{
namespace ecs
{
class MovementSystem : public ISystem
{
public:
    MovementSystem();
    void update(std::vector<COMP_TYPE> componentsToUse, float, void** component) override;
};
}
}
