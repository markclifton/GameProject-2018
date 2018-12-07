#include "icomponent.h"

namespace ecs
{
COMP_TYPE BaseComponent::RegisterComponent(COMP_SIZE size, COMP_CTOR ctor, COMP_DTOR dtor)
{
    COMP_TYPE type = availableComponents_.size();
    availableComponents_.emplace_back(std::tie(type, size, ctor, dtor));
    return type;
}

bool BaseComponent::ValidComponent(COMP_TYPE type)
{
    for(auto& component : availableComponents_)
    {
        if(std::get<0>(component) == type)
        {
            return true;
        }
    }
    return false;
}

RAWCOMP* BaseComponent::GetRaw(COMP_TYPE type)
{
    for(auto& component : availableComponents_)
    {
        if(std::get<0>(component) == type)
        {
            return &component;
        }
    }
    return nullptr;
}

std::vector<RAWCOMP> BaseComponent::availableComponents_;
}
