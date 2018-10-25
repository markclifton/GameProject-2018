#pragma once

#include <vector>

#include "drawable.h"
#include "drawablebasics.h"

//REFACTOR SOON
namespace drawable
{
    class DrawableObject : public drawable::Drawable
    {
    public:
        DrawableObject(Shader* shader);

        inline void setTextureIndex ( int index )
        {
            m_activeTexture = index;
            for(auto& vert : m_vertices)
            {
               vert.uv.z = m_activeTexture;
            }
        }

        void setTransform(glm::mat4 transform) override
        {
            m_transform = transform;
            for(auto& vert : m_vertices)
            {
                vert.model = m_transform;
            }
        }

    //TEMP
    public:
        std::vector<Vertex> m_vertices;
        std::vector<GLint> m_indices;

        int m_activeTexture { -1 };
    };
}
