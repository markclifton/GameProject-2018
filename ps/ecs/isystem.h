#pragma once

#include <algorithm>
#include <iostream>
#include <vector>

#include "icomponent.h"

namespace ps
{
namespace ecs
{
class ISystem
{
public:
    virtual ~ISystem() = default;
    inline virtual void update(std::vector<COMP_TYPE> /*componentsToUse*/, float /*timeDelta*/, void** /*components*/) = 0;

    inline bool containsComponent(const COMP_TYPE& type)
    {
        auto iter = std::find(components_.begin(), components_.end(), type);
        return iter != components_.end();
    }

    inline bool multithreaded() { return multithreaded_; }

protected:
    std::vector<COMP_TYPE> components_;
    bool multithreaded_ { false };
};
}
}
