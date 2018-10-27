#include "batchrenderer.h"

#include "layer.h"

#include <glm/gtc/type_ptr.hpp>

namespace drawable
{
    BatchRenderer::BatchRenderer(Shader* shader, glm::mat4 transform)
        : Drawable(shader)
        , m_tranform(transform)
    {
    }

    void BatchRenderer::submit(const int& numVerts, Vertex* vertices, const int& numIndices, GLint* indices)
    {
        m_changed = true; // nb: Not thread-safe

        //Copy over indices
        int startingIndex = static_cast<int>(m_vertices.size());
        for(int i=0; i<numIndices; ++i)
        {
            m_indices.push_back(indices[i] + startingIndex);
        }

        //Copy over vertices
        for(int i=0; i<numVerts; ++i)
        {
            m_vertices.push_back(vertices[i]);
        }
    }

    bool BatchRenderer::submit(DrawableObject* object)
    {
        Texture* objectTexture = object->getTexture();
        if(objectTexture)
        {
            bool found = false;
            for(size_t i = 0; i < m_textures.size(); i++)
            {
                if(m_textures[i] == objectTexture)
                {
                    object->setTextureId(static_cast<int>(i));
                    found = true;
                    break;
                }
            }

            if( !found )
            {
                if(m_textures.size() < 16)
                {
                    m_textures.push_back(objectTexture);
                    object->setTextureId(static_cast<int>(m_textures.size()));
                }
                else
                {
                    return false;
                }
            }

        }

        m_objects.push_back(std::make_pair(object, m_vertices.size()));

        submit(object->numVerts(), object->verts(), object->numIndices(), object->indices());

        //Update Lambda (Refactor maybe??)
        auto fn = [this, object](){
            for(size_t i=0; i<m_objects.size(); i++)
            {
                if(m_objects[i].first == object)
                {
                    for(int j=0; j<object->numVerts(); j++)
                    {
                        m_vertices[m_objects[i].second + j] = object->verts()[j];
                    }
                    m_changed = true;
                    break;
                }
            }
        };
        object->setUpdateFunc(fn);
        return true;
    }

    void BatchRenderer::draw(glm::mat4 transform)
    {
        if(m_shader != nullptr)
        {
            m_shader->bind();
            m_shader->setUniform("transform", transform * m_transform);
        }

        std::vector<int> data;
        for(size_t i = 0; i<m_textures.size(); i++)
        {
            data.push_back(static_cast<int>(i));
            m_textures[i]->bind(static_cast<uint>(i));
        }

        if(m_shader != nullptr && data.size() > 0)
        {
            m_shader->setUniform("myTextures", static_cast<int>(m_textures.size()), &data.front());
        }

        if(m_changed)
        {
            m_ibo.buffer(static_cast<long>(m_indices.size() * sizeof(GLint)), reinterpret_cast<void*>(&m_indices.front()));
            m_vbo.buffer(static_cast<long>(m_vertices.size() * sizeof(Vertex)), reinterpret_cast<void*>(&m_vertices.front()));
            m_changed = false;
        }

        m_ibo.bind();
        m_vbo.bind();

        glDrawElements(GL_TRIANGLES, static_cast<int>(m_indices.size()), GL_UNSIGNED_INT, nullptr);
    }
}
