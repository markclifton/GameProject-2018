#include "component.h"

#include <algorithm>

namespace ecs
{

void ComponentHandler::submit(IComponent* component)
{
    if(component == nullptr)
    {
        return;
    }

    std::lock_guard<std::mutex> lock(mutex_);
    components_.push_back(component);
}

void ComponentHandler::remove(unsigned int componentID)
{
    std::lock_guard<std::mutex> lock(mutex_);
    for(size_t index=0; index<components_.size(); index++)
    {
        if(components_[index]->getID() == componentID)
        {
            //auto componentTemp = components_[index];
            components_[index] = components_.back();
            components_.pop_back();
            //delete componentTemp; // Lets assume the entity will maintain these
            return;
        }
    }
}

}
