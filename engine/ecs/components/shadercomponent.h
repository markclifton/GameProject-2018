#pragma once

#include "ecs/icomponent.h"

#include "shaders/shader.h"

namespace ps
{
struct ShaderComponent : public ecs::IComponent<ShaderComponent>
{
    Shader* shader;
};
}
