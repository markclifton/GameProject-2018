#pragma once

#include <algorithm>
#include <iostream>
#include <vector>

#include "icomponent.h"

namespace ecs
{
class ISystem
{
public:
    virtual ~ISystem() = default;
    inline virtual void update(std::vector<COMP_TYPE> /*componentsToUse*/, float /*timeDelta*/, void** /*components*/) {}

    inline bool containsComponent(const COMP_TYPE& type)
    {
        auto iter = std::find(components_.begin(), components_.end(), type);
        return iter != components_.end();
    }

protected:
    std::vector<COMP_TYPE> components_;

};
}
