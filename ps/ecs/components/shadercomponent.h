#pragma once

#include "ps/ecs/icomponent.h"
#include "ps/shaders/shader.h"

namespace ps
{
struct ShaderComponent : public ecs::IComponent<ShaderComponent>
{
    Shader* shader;
};
}
