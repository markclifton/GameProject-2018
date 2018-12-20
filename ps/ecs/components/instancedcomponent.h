#pragma once

#include "ps/ecs/icomponent.h"

namespace ps
{
struct InstancedComponent : public ecs::IComponent<InstancedComponent>
{
};
}
