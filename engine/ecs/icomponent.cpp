#include "icomponent.h"

#include <iostream>

namespace ecs
{
COMP_TYPE BaseComponent::RegisterComponent(COMP_SIZE size, COMP_CTOR ctor, COMP_DTOR dtor)
{
    std::lock_guard<std::mutex> lock(registerMutex_);
    COMP_TYPE type = nextType_++;
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

const std::vector<RAWCOMP>& BaseComponent::GetAllComponents()
{
    return availableComponents_;
}

std::mutex BaseComponent::registerMutex_;
COMP_TYPE BaseComponent::nextType_ = 0;
std::vector<RAWCOMP> BaseComponent::availableComponents_;
}
