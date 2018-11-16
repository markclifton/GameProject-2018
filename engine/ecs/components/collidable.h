#pragma once

#include "component.h"
#include "glm/vec3.hpp"

namespace ecs
{

//TODO: BBHier
struct BoundingBox
{
    glm::vec3 min {0,0,0};
    glm::vec3 max {0,0,0};
};

class Collidable : public IComponent
{
public:
    virtual ~Collidable() = default;

    inline void setPosition(const glm::vec3& position) { position_ = position; }
    inline void setBoundingBox(const BoundingBox& bbox) { bbox_ = bbox; }

    glm::vec3 getPosition() { return position_; }
    BoundingBox getBoundingBox() { return bbox_; }

private:
    glm::vec3 position_ {0,0,0};
    BoundingBox bbox_;
};

}
