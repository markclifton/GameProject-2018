#pragma once

#include <memory>

#include "entity.h"
#include "ecs/components/collidable.h"

//TEST CLASS
namespace ecs
{

class Simple : public IEntity
{
public:
    Simple(glm::vec3 pos, glm::vec3 min, glm::vec3 max)
    {
        Collidable* collidable = new Collidable();
        collidable->setPosition(pos);

        BoundingBox bbox;
        bbox.min = min;
        bbox.max = max;
        collidable->setBoundingBox(bbox);

        ComponentHandler::submit(std::shared_ptr<IComponent>(collidable));
    }

private:
};

}
