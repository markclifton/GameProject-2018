#pragma once

#include "camera/camera.h"
#include "drawable/renderers/layer.h"
#include "managers/shadermanager.h"
#include "managers/texturemanager.h"
#include "managers/windowmanager.h"

#include "lights/point.h"
#include "lights/spot.h"

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
    drawable::renderer::Layer m_stack;

    Camera3D m_camera;
    Camera3D m_shadowCamera;

    std::vector<lights::PointLight> m_pointlights;
    std::vector<lights::SpotLight> m_spotlights;

    std::unique_ptr<Texture> m_shadowTexture;
};
