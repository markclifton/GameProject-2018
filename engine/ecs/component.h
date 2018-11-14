#pragma once

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
    inline const unsigned int& getID(){ return componentID_; }

private:
    unsigned int componentID_ {0};
};

class ComponentHandler
{
public:
    void submit(IComponent* component);
    void remove(unsigned int componentID);

protected:
    std::vector<IComponent*> components_;
    std::mutex mutex_;
};

}
