#include "layer.h"

namespace drawable
{
    Layer::Layer(managers::ShaderManager& sm, managers::TextureManager& tm)
        : m_sm(sm), m_tm(tm)
    {
        m_allChildren.emplace_back();
        m_allChildren.emplace_back();
    }

    Layer::~Layer()
    {
        while( !m_allChildren[1].empty() )
        {
            auto back = m_allChildren[1].back();
            m_allChildren[1].pop_back();
            delete back;
        }
    }

    void Layer::draw(glm::mat4 transform)
    {
        for(auto& setOfChildren : m_allChildren)
        {
            for(auto& child : setOfChildren)
            {
                auto shader = child->getShader();
                shader->bind();

                child->draw(transform);
            }
        }
    }

    void Layer::submit(Drawable* drawable, bool ownThis)
    {
        m_allChildren[ownThis ? 1 : 0].push_back(drawable);
    }
}
