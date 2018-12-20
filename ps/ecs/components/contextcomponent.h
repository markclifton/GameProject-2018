#pragma once

#include <string>

#include "ps/ecs/icomponent.h"

namespace ps
{
struct ContextComponent : public ecs::IComponent<ContextComponent>
{
    std::string context {""};
};
}
