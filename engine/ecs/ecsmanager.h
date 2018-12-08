#pragma once

#include <algorithm>
#include <map>
#include <vector>

#include "icomponent.h"
#include "ientity.h"
#include "isystem.h"

namespace ecs
{
class ECSManager
{
public:
    void updateSystems(std::vector<COMP_TYPE> ComponentsToUse);
    void addSystem(const size_t& SystemID, ISystem* system);
    void removeSystem(const size_t& SystemID);
    void addEntity(IEntity* entity);
    void removeEntity(IEntity* entity);
    bool containsEntity(IEntity* entity);

private:
    std::map<size_t, ISystem*> systems_;
    std::vector<IEntity*> entities_;

};
}
