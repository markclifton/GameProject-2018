#include "context.h"

namespace ps
{
ContextBase::ContextBase()
    : soundManager_(managers::SoundManager::Get())
    , shaderManager_(managers::ShaderManager::Get())
    , textureManager_(managers::TextureManager::Get())
    , windowManager_(managers::WindowManager::Get())
{
    loadResources();
}

void ContextBase::run()
{
}

void ContextBase::loadResources()
{
}
}
