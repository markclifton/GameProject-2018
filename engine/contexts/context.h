#pragma once

#include "camera/camera.h"
#include "drawable/renderers/layer.h"
#include "managers/soundmanager.h"
#include "managers/shadermanager.h"
#include "managers/texturemanager.h"
#include "managers/windowmanager.h"

#include "lights/point.h"
#include "lights/spot.h"

#include "ecs/ecsmanager.h"
#include "ecs/systems/renderingsystem.h"

class Context
{
public:
    Context(managers::SoundManager& soundManager, managers::ShaderManager& shaderManager, managers::TextureManager& textureManager, managers::WindowManager& windowManager);
    void run();
    void loadResources();

private:
    managers::SoundManager& soundManager_;
    managers::ShaderManager& shaderManager_;
    managers::TextureManager& textureManager_;
    managers::WindowManager& windowManager_;
    drawable::renderer::Layer stack_;

    Camera3D m_camera;
    Camera3D shadowCamera_;

    std::vector<lights::PointLight> pointlights_;
    std::vector<lights::SpotLight> spotlights_;

    Texture* shadowTexture_ {nullptr};

    ecs::ECSManager ecsManager_;
    ecs::RendererSystem renderingSystem_;
};
