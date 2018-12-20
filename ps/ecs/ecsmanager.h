#pragma once

#include <algorithm>
#include <map>
#include <memory>
#include <vector>

#include "icomponent.h"
#include "ientity.h"
#include "isystem.h"

namespace ps
{
namespace ecs
{
class ECSManager
{
    ECSManager() {}
public:
    static ECSManager& get()
    {
        static ECSManager manager;
        return manager;
    }

    void updateSystems(const std::string& context, std::vector<COMP_TYPE> ComponentsToUse);
    void addSystem(const size_t& SystemID, std::shared_ptr<ISystem> system);
    void removeSystem(const size_t& SystemID);
    void addEntity(std::shared_ptr<IEntity> entity);

    inline void reset()
    {
        systems_.clear();
        entities_.clear();
    }
    //void removeEntity(IEntity* entity); //FIXME!

private:
    ECSManager(ECSManager const&) = delete;
    void operator=(ECSManager const&) = delete;

    std::map<size_t, std::shared_ptr<ISystem>> systems_;
    std::vector<std::shared_ptr<IEntity>> entities_;

};
}
}
