#pragma once

#include "ps/ecs/icomponent.h"
#include "ps/textures/texture.h"

namespace ps
{
struct TextureComponent : public ecs::IComponent<TextureComponent>
{
    Texture* texture;
};
}
