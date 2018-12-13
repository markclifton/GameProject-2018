#pragma once

#include <algorithm>
#include <map>
#include <memory>
#include <vector>

#include "icomponent.h"
#include "ientity.h"
#include "isystem.h"

namespace ecs
{
class ECSManager
{
public:
    static ECSManager& get()
    {
        static ECSManager manager;
        return manager;
    }

    void updateSystems(std::vector<COMP_TYPE> ComponentsToUse);
    void addSystem(const size_t& SystemID, std::shared_ptr<ISystem> system);
    void removeSystem(const size_t& SystemID);
    void addEntity(std::shared_ptr<IEntity> entity);
    //void removeEntity(IEntity* entity); //FIXME!

private:
    std::map<size_t, std::shared_ptr<ISystem>> systems_;
    std::vector<std::shared_ptr<IEntity>> entities_;

};
}
