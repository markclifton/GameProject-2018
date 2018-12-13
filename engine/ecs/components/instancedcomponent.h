#pragma once

#include "ecs/icomponent.h"

struct InstancedComponent : public ecs::IComponent<InstancedComponent>
{
};
