#pragma once

#include <vector>

#include "ps/drawable/drawable.h"
#include "ps/managers/shadermanager.h"
#include "ps/managers/texturemanager.h"

namespace ps
{
namespace drawable
{
namespace renderer
{
class Layer
{
public:
    Layer(managers::ShaderManager& sm, managers::TextureManager& tm);
    ~Layer();

    void draw(glm::mat4 transform = glm::mat4(1.f));
    void submit(Drawable* drawable, bool ownThis = true);

private:
    std::vector<std::vector<Drawable*>> m_allChildren;

    managers::ShaderManager& m_sm;
    managers::TextureManager& m_tm;
};
}
}
}
