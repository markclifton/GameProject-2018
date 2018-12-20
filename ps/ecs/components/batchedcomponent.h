#pragma once

#include "ps/ecs/icomponent.h"

namespace ps
{
struct BatchedComponent : public ecs::IComponent<BatchedComponent>
{
};
}
