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

    std::function<void()> BatchRenderer::submit(DrawableObject* object)
    {
        m_objects.push_back(std::make_pair(object, m_vertices.size()));

        // This is dumb, FIX ME
        object->setTextureIndex(static_cast<int>(m_textures.size()) + 1 );

        submit(static_cast<int>(object->m_vertices.size()), &object->m_vertices.front(), static_cast<int>(object->m_indices.size()), &object->m_indices.front());

        auto objectTextures = object->getTextures();
        for(auto& texture : objectTextures)
        {
            //TODO: There is a good chance there will be duplicates
            m_textures.push_back(texture);
        }

        //Update Lambda (Refactor maybe??)
        auto fn = [this, object](){
            for(size_t i=0; i<m_objects.size(); i++)
            {
                if(m_objects[i].first == object)
                {
                    for(size_t j=0; j<object->m_vertices.size(); j++)
                    {
                        m_vertices[m_objects[i].second + j] = object->m_vertices[j];
                    }
                    m_changed = true;
                    break;
                }
            }
        };
        return fn;
    }

    void BatchRenderer::draw(glm::mat4 transform)
    {
        if(m_shader != nullptr)
        {
            m_shader->bind();
            m_shader->setUniform("transform", transform * m_transform);
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
