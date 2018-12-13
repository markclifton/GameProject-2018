#include "ecsmanager.h"

namespace ecs
{
void ECSManager::updateSystems(std::vector<COMP_TYPE> ComponentsToUse)
{
    if(ComponentsToUse.size() == 0)
    {
        return;
    }

    //Make list of Components that need processed
    std::vector<std::vector<void*>> componentsToUpdate;
    for(auto& entity : entities_)
    {
        bool isValid = true;
        for(auto& component : ComponentsToUse)
        {
            if(entity->NumComponentsForType(component) == 0)
            {
                isValid = false;
                break;
            }
        }

        if(isValid)
        {
            std::vector<void*> componentUpdateVector;
            for(auto& component : ComponentsToUse)
            {
                componentUpdateVector.push_back(entity->GetComponentByTypeAndIndex(component, 0));
            }
            componentsToUpdate.push_back(componentUpdateVector);
        }
    }

    //Process Components
    for(auto& system : systems_)
    {
        bool validSystem = true;
        for(auto& component : ComponentsToUse)
        {
            if(!system.second->containsComponent(component))
            {
                validSystem = false;
                break;
            }
        }

        if(validSystem)
        {
            for(auto& component : componentsToUpdate)
            {
                system.second->update(ComponentsToUse, 0, &component.front());
            }
        }
    }
}

void ECSManager::addSystem(const size_t& SystemID, ISystem* system)
{
    removeSystem(SystemID);
    systems_[SystemID] = system;
}

void ECSManager::removeSystem(const size_t& SystemID)
{
    systems_.erase(SystemID);
}

void ECSManager::addEntity(IEntity* entity)
{
    if(!containsEntity(entity))
    {
        entities_.push_back(entity);
    }
}

void ECSManager::removeEntity(IEntity* entity)
{
    auto iter = std::find_if(entities_.begin(), entities_.end(), [entity](IEntity* curEntity){ return curEntity == entity; });
    if(iter != entities_.end())
    {
        *iter = entities_.back();
        entities_.pop_back();
    }
}

bool ECSManager::containsEntity(IEntity* entity)
{
    auto iter = std::find_if(entities_.begin(), entities_.end(), [entity](IEntity* curEntity){ return curEntity == entity; });
    return iter != entities_.end();
}
}
