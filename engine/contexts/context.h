#pragma once

#include "camera/camera.h"
#include "drawable/layer.h"
#include "managers/shadermanager.h"
#include "managers/texturemanager.h"
#include "managers/windowmanager.h"

class Context
{
public:
    Context(managers::ShaderManager& shaderManager, managers::TextureManager& textureManager, managers::WindowManager& windowManager);
    void run();
    void loadResources();

private:
    managers::ShaderManager& m_shaderManager;
    managers::TextureManager& m_textureManager;
    managers::WindowManager& m_windowManager;
    drawable::Layer m_stack;

    Camera3D m_camera;
};
