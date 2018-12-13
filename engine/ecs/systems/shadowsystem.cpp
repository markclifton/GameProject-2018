#include "shadowsystem.h"

#include "glm/matrix.hpp"

#include <algorithm>
#include <iostream>

#include "shaders/shader.h"

#include "ecs/entities/drawableentity.h"

#include "ecs/components/cameracomponent.h"
#include "ecs/components/shadercomponent.h"
#include "ecs/components/texturecomponent.h"

namespace ecs
{
ShadowSystem::ShadowSystem()
{
    components_.push_back(CameraComponent::Type);
    components_.push_back(ShaderComponent::Type);
    components_.push_back(TextureComponent::Type);
}

void ShadowSystem::update(std::vector<COMP_TYPE> componentsToUse, float /*delta*/, void** component)
{
    auto baseComponent = reinterpret_cast<BaseComponent*>(*component);
    //auto entity = reinterpret_cast<drawable::DrawableObject*>(baseComponent->entityHandle);

    //Update camera

    //Bind shader

    //Bind texture

    //Call render system

}


}
