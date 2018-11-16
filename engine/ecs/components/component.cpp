#include "component.h"

#include <algorithm>

namespace ecs
{

void ComponentHandler::submit(std::shared_ptr<IComponent> component)
{
    if(component == nullptr)
    {
        return;
    }

    std::lock_guard<std::mutex> lock(mutex_);
    ownedComponents_.push_back(component);
    ownedComponents_.back()->setID(++id);
}

void ComponentHandler::submit(std::weak_ptr<IComponent> component)
{
    std::lock_guard<std::mutex> lock(mutex_);
    sharedComponents_.push_back(component);
}

void ComponentHandler::remove(unsigned int componentID)
{
    std::lock_guard<std::mutex> lock(mutex_);
    for(size_t index=0; index<ownedComponents_.size(); index++)
    {
        if(ownedComponents_[index]->getID() == componentID)
        {
            //auto componentTemp = components_[index];
            ownedComponents_[index] = ownedComponents_.back();
            ownedComponents_.pop_back();
            //delete componentTemp; // Lets assume the entity will maintain these
            return;
        }
    }

    for(size_t index=0; index<sharedComponents_.size(); index++)
    {
        if(sharedComponents_[index].lock()->getID() == componentID)
        {
            //auto componentTemp = components_[index];
            sharedComponents_[index] = sharedComponents_.back();
            sharedComponents_.pop_back();
            //delete componentTemp; // Lets assume the entity will maintain these
            return;
        }
    }
}

}
