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

    void BatchRenderer::draw(glm::mat4 transform)
    {
        if(m_shader != nullptr)
        {
            m_shader->bind();
            m_shader->setUniform("model", transform * m_transform);
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
