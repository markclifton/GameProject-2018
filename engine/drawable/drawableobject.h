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
    struct bbox
    {
        glm::vec3 min {0};
        glm::vec3 max {0};
    };

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

        const bbox& calculateBBox()
        {
            for(auto& vertex : m_vertices)
            {
                m_bbox.min.x = std::min(m_bbox.min.x, vertex.pos.x);
                m_bbox.min.y = std::min(m_bbox.min.y, vertex.pos.y);
                m_bbox.min.z = std::min(m_bbox.min.z, vertex.pos.z);
                m_bbox.max.x = std::max(m_bbox.max.x, vertex.pos.x);
                m_bbox.max.y = std::max(m_bbox.max.y, vertex.pos.y);
                m_bbox.max.z = std::max(m_bbox.max.z, vertex.pos.z);
            }

            return m_bbox;
        }

    protected:
        std::vector<Vertex> m_vertices;
        std::vector<GLint> m_indices;
        Texture* m_texture {nullptr};

        buffers::BasicVBO m_vertexBuffer;
        buffers::IndexBuffer m_indicesBuffer;
        bool m_changed { true };

        std::function<void()> m_updateFunc;

        bbox m_bbox;
    };
}
