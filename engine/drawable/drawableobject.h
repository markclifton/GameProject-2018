#pragma once

#include <functional>
#include <vector>

#include "buffers/indexbuffer.h"
#include "buffers/vertexbuffers/vb_basic.h"
#include "drawable.h"
#include "drawablebasics.h"
#include "textures/texture.h"

//REFACTOR SOON : Move to cpp
namespace drawable
{
    class DrawableObject : public drawable::Drawable
    {
    public:
        DrawableObject(Shader* shader);

        void setTransform(glm::mat4 transform) override
        {
            m_transform = transform;
            for(auto& vert : m_vertices)
            {
                vert.model = m_transform;
            }
            update();
        }

        void setTextureId(const int& id)
        {
            for(auto& vert : m_vertices)
            {
                vert.uv.z = id;
            }
            update();
        }
        void setTexture( Texture* texture ) { m_texture = texture; setTextureId(0); }
        Texture* getTexture() { return m_texture; }

        Vertex* verts() { return &m_vertices.front(); }
        int numVerts() { return static_cast<int>(m_vertices.size()); }

        GLint* indices() { return &m_indices.front(); }
        int numIndices() { return static_cast<int>(m_indices.size()); }

        void setUpdateFunc(std::function<void()> fn)
        {
            m_updateFunc = fn;
        }

        void update()
        {
            if(m_updateFunc)
            {
                m_updateFunc();
            }
            else
            {
                m_changed = true;
            }
        }

    protected:
        std::vector<Vertex> m_vertices;
        std::vector<GLint> m_indices;
        Texture* m_texture {nullptr};

        buffers::BasicVBO m_vertexBuffer;
        buffers::IndexBuffer m_indicesBuffer;
        bool m_changed { true };

        std::function<void()> m_updateFunc;
    };
}
