#pragma once

#include <map>
#include <mutex>
#include <vector>

#include "icomponent.h"

namespace ps
{
namespace
{
unsigned long GetUniqueID()
{
    static std::mutex mutex;
    std::lock_guard<std::mutex> lock(mutex);
    static unsigned long id = 0;
    return ++id;
}
}

namespace ecs
{
class IEntity
{
public:
    IEntity(const std::string& context)
        : id_(GetUniqueID())
        , context_(context)
    {}

    void AddComponentOfType(const COMP_TYPE& type, void* component)
    {
        if(NumComponentsForType(type) == 0)
        {
            componentsMap_[type] = std::vector<void*>();
        }
        componentsMap_[type].push_back(component);
    }

    size_t NumComponentsForType(const COMP_TYPE& type)
    {
        if(componentsMap_.count(type) > 0)
        {
            return componentsMap_[type].size();
        }
        return 0;
    }

    void* GetComponentByTypeAndIndex(const COMP_TYPE& type, size_t index)
    {
        auto numComponents = NumComponentsForType(type);
        if(numComponents == 0 || index >= numComponents)
        {
            return nullptr;
        }
        return componentsMap_[type][index];
    }

    inline const std::string& getContext() { return context_; }

private:
    const unsigned long id_;
    const std::string context_;
    std::map<COMP_TYPE, std::vector<void*>> componentsMap_;
};
}
}
