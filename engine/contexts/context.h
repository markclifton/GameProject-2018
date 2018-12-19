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
#include "ecs/systems/shadowsystem.h"
#include "ecs/entities/shadowentity.h"

namespace ps
{
class ContextBase
{
public:
    ContextBase();
    virtual void run();
    virtual void loadResources();

protected:
    managers::SoundManager& soundManager_;
    managers::ShaderManager& shaderManager_;
    managers::TextureManager& textureManager_;
    managers::WindowManager& windowManager_;
};
}
