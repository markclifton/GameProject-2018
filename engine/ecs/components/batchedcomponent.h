#pragma once

#include "ecs/icomponent.h"

namespace ps
{
struct BatchedComponent : public ecs::IComponent<BatchedComponent>
{
};
}
