#pragma once

#include "../drawable/layer.h"
#include "../managers/shadermanager.h"

class Context
{
public:
    Context(managers::ShaderManager& shaderManager);

    void run();

private:
    managers::ShaderManager& m_shaderManager;
    drawable::Layer m_stack;
};
