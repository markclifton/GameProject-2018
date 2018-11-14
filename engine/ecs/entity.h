#pragma once

#include "component.h"


/*  Grouping of Raw Data into a "thing"
 *
 *  Example :
 *  Entity : Entity1
 *  Component :  Position
 *  Component :  BBox
 */

namespace ecs
{
class ISystem;

class IEntity : public ComponentHandler
{
    friend class ISystem;
public:
};
}
