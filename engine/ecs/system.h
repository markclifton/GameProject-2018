#pragma once

#include <vector>

#include "component.h"

/*  System that executes actions on Components
 *
 *  Example :
 *  System : Movement System (Moves objects)
 *  Component :  Position
 */

namespace ecs
{
    class ISystem : ComponentHandler
    {
    public:
    };
}
