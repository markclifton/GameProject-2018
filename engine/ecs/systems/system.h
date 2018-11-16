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

#include "ecs/components/collidable.h"

namespace ecs
{
class ISystem : public ComponentHandler
{
public:

    //TEMP
    void submit(IEntity& entity)
    {
        for(std::shared_ptr<IComponent>& component : entity.ownedComponents_)
        {
            IComponent* raw = component.get();
            if(dynamic_cast<Collidable*>(raw) != nullptr)
            {
                ComponentHandler::submit(std::weak_ptr<IComponent>(component));
                printf("Collidable Component Found!\n");
            }
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

            auto spCurrent = sharedComponents_[index].lock();
            for(size_t indexInner=0; indexInner<sharedComponents_.size(); indexInner++)
            {
                auto spComparison = sharedComponents_[index].lock();
                if(spComparison && spComparison->getID() != spCurrent->getID())
                {
                    printf("Comparing!\n");
                }
            }
        }
    }
};
}
