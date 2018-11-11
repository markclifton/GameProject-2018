#include "batch.h"

#include "layer.h"

#include <glm/gtc/type_ptr.hpp>

namespace drawable
{
namespace renderer
{
Batch::Batch(Shader* shader, glm::mat4 transform)
    : Drawable(shader)
    , m_tranform(transform)
{
    shader->bind();

    int position = shader->getAttribLocation("position");
    if(position >= 0)
    {
        m_vbo.useVertexAttrib(static_cast<uint32_t>(position), 3, GL_FLOAT, false, sizeof(Vertex), offsetof(Vertex, pos));
    }

    int color = shader->getAttribLocation("color");
    if(color >= 0)
    {
        m_vbo.useVertexAttrib(static_cast<uint32_t>(color), 4, GL_FLOAT, false, sizeof(Vertex), offsetof(Vertex, color));
    }

    int uv = shader->getAttribLocation("uv");
    if(uv >= 0)
    {
        m_vbo.useVertexAttrib(static_cast<uint32_t>(uv), 3, GL_FLOAT, false, sizeof(Vertex), offsetof(Vertex, uv));
    }

    int normal = shader->getAttribLocation("normal");
    if(normal >= 0)
    {
        m_vbo.useVertexAttrib(static_cast<uint32_t>(normal), 3, GL_FLOAT, false, sizeof(Vertex), offsetof(Vertex, normal));
    }

    int model = shader->getAttribLocation("model");
    if(model >= 0)
    {
        m_vbo.useVertexAttrib(static_cast<uint32_t>(model + 0), 4, GL_FLOAT, false, sizeof(Vertex), 0 * sizeof(glm::vec4) + offsetof(Vertex, model));
        m_vbo.useVertexAttrib(static_cast<uint32_t>(model + 1), 4, GL_FLOAT, false, sizeof(Vertex), 1 * sizeof(glm::vec4) + offsetof(Vertex, model));
        m_vbo.useVertexAttrib(static_cast<uint32_t>(model + 2), 4, GL_FLOAT, false, sizeof(Vertex), 2 * sizeof(glm::vec4) + offsetof(Vertex, model));
        m_vbo.useVertexAttrib(static_cast<uint32_t>(model + 3), 4, GL_FLOAT, false, sizeof(Vertex), 3 * sizeof(glm::vec4) + offsetof(Vertex, model));
    }
}

void Batch::submit(const int& numVerts, Vertex* vertices, const int& numIndices, GLint* indices)
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

bool Batch::submit(DrawableObject* object)
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
                object->setTextureId(static_cast<int>(m_textures.size()) - 1);
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
                for(size_t j=0; j<static_cast<size_t>(object->numVerts()); j++)
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

void Batch::draw(glm::mat4 transform)
{
    if(m_shader != nullptr)
    {
       // m_shader->bind();
        m_shader->setUniform("transform", transform * m_transform);
    }

    std::vector<int> data;
    data.push_back(0);
    for(size_t i = 0; i<m_textures.size(); i++)
    {
        data.push_back(static_cast<int>(i) + 1);
        m_textures[i]->bind(static_cast<uint32_t>(i) + 1);
    }

    if(m_shader != nullptr && data.size() > 0)
    {
        m_shader->setUniform("textures", static_cast<int>(data.size()), &data.front());
    }

    if(m_changed)
    {
        m_ibo.buffer(static_cast<long>(m_indices.size() * sizeof(GLint)), reinterpret_cast<void*>(&m_indices.front()));
        m_vbo.buffer(static_cast<long>(m_vertices.size() * sizeof(Vertex)), reinterpret_cast<void*>(&m_vertices.front()));
        m_changed = false;
    }

    m_ibo.bind();
    m_vbo.bind();

    glDrawElements(m_drawType, static_cast<int>(m_indices.size()), GL_UNSIGNED_INT, nullptr);
}
}
}
