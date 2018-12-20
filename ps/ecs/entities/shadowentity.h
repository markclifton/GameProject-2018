#pragma once

#include "ps/ecs/ientity.h"

#include "ps/ecs/components/cameracomponent.h"
#include "ps/ecs/components/shadercomponent.h"
#include "ps/ecs/components/texturecomponent.h"

namespace ps
{
namespace ecs
{
class ShadowEntity : public ecs::IEntity
{
public:
    ShadowEntity(const std::string& context, Shader* shader, Texture* texture);

    CameraComponent cameraComponent;
};
}
}
