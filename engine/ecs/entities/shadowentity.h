#pragma once

#include "ecs/ientity.h"

#include "ecs/components/cameracomponent.h"
#include "ecs/components/shadercomponent.h"
#include "ecs/components/texturecomponent.h"

namespace ps
{
namespace ecs
{
class ShadowEntity : public ecs::IEntity
{
public:
    ShadowEntity(Shader* shader, Texture* texture);

    CameraComponent cameraComponent;
};
}
}
