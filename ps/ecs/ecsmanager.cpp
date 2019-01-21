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

        int runningCount = 0;
        if(validSystem)
        {
            std::mutex systemMutex;
            for(auto& component : componentsToUpdate)
            {
                if(system.second->multithreaded())
                {
                    auto front = &component.front();
                    auto f = [&systemMutex, &runningCount, system, ComponentsToUse, front](){
                        {
                            std::lock_guard<std::mutex> lock(systemMutex);
                            runningCount++;
                        }
                        system.second->update(ComponentsToUse, 0, front);
                        {
                            std::lock_guard<std::mutex> lock(systemMutex);
                            runningCount--;
                        }
                    };

                    threadPool_.enqueue(f);
                }
                else
                {
                    system.second->update(ComponentsToUse, 0, &component.front());
                }
            }
        }

        using namespace std::chrono_literals;
        while(runningCount > 0)
        {
            std::this_thread::sleep_for(20ns);
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
    entities_.emplace_back(entity);
}
}
