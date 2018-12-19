#pragma once

#include "ecs/icomponent.h"

namespace ps
{
struct InstancedComponent : public ecs::IComponent<InstancedComponent>
{
};
}
