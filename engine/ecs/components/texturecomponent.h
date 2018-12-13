#pragma once

#include "ecs/icomponent.h"

#include "textures/texture.h"

struct TextureComponent : public ecs::IComponent<TextureComponent>
{
    Texture* texture;
};
