#include "layer.h"

namespace drawable
{
    Layer::Layer(Shader* shader)
        : Drawable(shader)
    {}

    Layer::~Layer()
    {
        while( !m_ownedChildren.empty() )
        {
            auto back = m_ownedChildren.back();
            m_ownedChildren.pop_back();
            delete back;
        }
    }

    void Layer::draw(glm::mat4 transform)
    {
        if(m_shader != nullptr)
        {
            m_shader->bind();
            m_shader->setUniform("model", transform);
        }

        for(auto& child : m_children)
        {
            child->draw(transform * m_transform);
        }

        for(auto& child : m_ownedChildren)
        {
            child->draw(transform * m_transform);
        }
    }

    void Layer::submit(Drawable* drawable, bool ownThis)
    {
        if( ownThis )
        {
            m_ownedChildren.push_back(drawable);
        }
        else
        {
            m_children.push_back(drawable);
        }
    }
}
