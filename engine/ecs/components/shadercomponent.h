#pragma once

#include "ecs/icomponent.h"

#include "shaders/shader.h"

struct ShaderComponent : public ecs::IComponent<ShaderComponent>
{
    Shader* shader;
};
