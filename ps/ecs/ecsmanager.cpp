#include "ecsmanager.h"

#include <thread>

namespace ps
{
void ECSManager::updateSystems(const std::string& context, std::vector<ecs::COMP_TYPE> ComponentsToUse)
{
    if(ComponentsToUse.size() == 0)
    {
        return;
    }

    //Make list of Components that need processed
    std::vector<std::vector<void*>> componentsToUpdate;
    for(auto& entity : entities_)
    {
        auto entityRaw = reinterpret_cast<ecs::IEntity*>(entity.get());
        if(entityRaw->getContext() != context)
        {
            continue;
        }

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
                if(system.second->multithreaded())
                {
                    auto task = [this, system, ComponentsToUse, component](){
                        threadActive();
                        system.second->update(ComponentsToUse, 0, component[0]);
                        threadInactive();
                    };

                    threadPool_.enqueue(task);
                }
                else
                {
                    system.second->update(ComponentsToUse, 0, component[0]);
                }
            }

            while(activeThreads_ != 0)
            {
                using namespace std::chrono_literals;
                std::this_thread::sleep_for(10ns);
            }
        }
    }
}

void ECSManager::addSystem(const size_t& SystemID, std::shared_ptr<ecs::ISystem> system)
{
    removeSystem(SystemID);
    systems_[SystemID] = system;
}

void ECSManager::removeSystem(const size_t& SystemID)
{
    systems_.erase(SystemID);
}

void ECSManager::addEntity(std::shared_ptr<ecs::IEntity> entity)
{
    entities_.push_back(entity);
}
}
