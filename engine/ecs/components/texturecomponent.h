#pragma once

#include "ecs/icomponent.h"

#include "textures/texture.h"

namespace ps
{
struct TextureComponent : public ecs::IComponent<TextureComponent>
{
    Texture* texture;
};
}
