#pragma once

#include <algorithm>
#include <map>
#include <memory>
#include <vector>

#include "icomponent.h"
#include "ientity.h"
#include "isystem.h"

#include "ps/utils/threadpool.h"

namespace ps
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

    void updateSystems(const std::string& context, std::vector<ecs::COMP_TYPE> ComponentsToUse);
    void addSystem(const size_t& SystemID, std::shared_ptr<ecs::ISystem> system);
    void removeSystem(const size_t& SystemID);
    void addEntity(std::shared_ptr<ecs::IEntity> entity);

    inline void reset()
    {
        systems_.clear();
        entities_.clear();
    }
    //void removeEntity(IEntity* entity); //FIXME!

    std::map<size_t, std::shared_ptr<ecs::ISystem>> systems_;
    std::vector<std::shared_ptr<ecs::IEntity>> entities_;

private:
    ECSManager(ECSManager const&) = delete;
    void operator=(ECSManager const&) = delete;
};
}
