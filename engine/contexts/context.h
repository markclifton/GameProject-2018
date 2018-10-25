#pragma once

#include "drawable/layer.h"
#include "managers/shadermanager.h"
#include "managers/texturemanager.h"

//TEMP
#include <vector>
#include "textures/texture.h"

class Context
{
public:
    Context(managers::ShaderManager& shaderManager, managers::TextureManager& textureManager);
    void run();

private:
    managers::ShaderManager& m_shaderManager;
    managers::TextureManager& m_textureManager;
    drawable::Layer m_stack;
};
