#pragma once

#include "drawable/layer.h"
#include "drawable/model.h" //TEMP
#include "managers/shadermanager.h"
#include "managers/texturemanager.h"

class Context
{
public:
    Context(managers::ShaderManager& shaderManager, managers::TextureManager& textureManager);
    void run();
    void loadResources();

private:
    managers::ShaderManager& m_shaderManager;
    managers::TextureManager& m_textureManager;
    drawable::Layer m_stack;

    drawable::Model* m;
};
