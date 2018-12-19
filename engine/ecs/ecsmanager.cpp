#include "ecsmanager.h"

namespace ps
{
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
        auto entityRaw = reinterpret_cast<IEntity*>(entity.get());


        bool isValid = true;
        for(auto& component : ComponentsToUse)
        {
            if(entityRaw->NumComponentsForType(component) == 0)
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
                componentUpdateVector.push_back(entityRaw->GetComponentByTypeAndIndex(component, 0));
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

void ECSManager::addSystem(const size_t& SystemID, std::shared_ptr<ISystem> system)
{
    removeSystem(SystemID);
    systems_[SystemID] = system;
}

void ECSManager::removeSystem(const size_t& SystemID)
{
    systems_.erase(SystemID);
}

void ECSManager::addEntity(std::shared_ptr<IEntity> entity)
{
    entities_.emplace_back(entity);
}

}
}
