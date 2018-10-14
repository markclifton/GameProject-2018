#pragma once

#include <vector>

#include "drawable.h"

namespace drawable
{
    class Layer : public Drawable
    {
    public:
        Layer(Shader* shader);
        ~Layer() override;

        void draw(glm::mat4 transform = glm::mat4(1.f)) override;
        void submit(Drawable* drawable, bool ownThis = true);

    private:
        std::vector<Drawable*> m_children;
        std::vector<Drawable*> m_ownedChildren;
    };
}
