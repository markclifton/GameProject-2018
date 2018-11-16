#pragma once

#include <memory>
#include <mutex>
#include <vector>

/*  Raw Data
 *
 *  Example :
 *  Component :  Position
 *
 */

namespace ecs
{
class IComponent
{
public:
    inline void setID(const unsigned int& ID) { componentID_ = ID; } //TODO: Generate Automatically
    inline const unsigned int& getID(){ return componentID_; }

    inline virtual void test(){} //THIS IS DUMB

private:
    unsigned int componentID_ {0};
};

class ComponentHandler
{
public:
    void submit(std::shared_ptr<IComponent> component);
    void submit(std::weak_ptr<IComponent> component);
    void remove(unsigned int componentID);

protected:
    std::vector<std::shared_ptr<IComponent>> ownedComponents_;
    std::vector<std::weak_ptr<IComponent>> sharedComponents_;

    std::mutex mutex_;

    unsigned int id {0};
};

}
