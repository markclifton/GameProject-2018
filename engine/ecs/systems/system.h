#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ecs/components/component.h"
#include "ecs/entities/entity.h"

/*  System that executes actions on Components
 *
 *  Example :
 *  System : Movement System (Moves objects)
 *  Component :  Position
 */

namespace ecs
{
class ISystem : public ComponentHandler
{
public:

    //TEMP
    void submit(IEntity& entity)
    {
        for(auto& component : entity.ownedComponents_)
        {
            ComponentHandler::submit(std::weak_ptr<IComponent>(component));
        }
    }

    void doWork()
    {
        for(size_t index=0; index<sharedComponents_.size(); index++)
        {
            //Remove Current and Reset Index;
            if(sharedComponents_[index].expired())
            {
                sharedComponents_[index] = sharedComponents_.back();
                sharedComponents_.pop_back();
                index--;
                continue;
            }

            auto spComponent = sharedComponents_[index].lock();
            std::cout << "DoingWork with: " << spComponent->getID() << std::endl;
        }
    }
};
}
