#pragma once

#include <vector>

#include "drawable.h"
#include "managers/shadermanager.h"
#include "managers/texturemanager.h"

namespace drawable
{
    class Layer
    {
    public:
        Layer(managers::ShaderManager& sm, managers::TextureManager& tm);
        ~Layer();

        void draw(glm::mat4 transform = glm::mat4(1.f));
        void submit(Drawable* drawable, bool ownThis = true);

    private:
        //Todo: consider ordering
        std::vector<std::vector<Drawable*>> m_allChildren;

        managers::ShaderManager& m_sm;
        managers::TextureManager& m_tm;
    };
}
