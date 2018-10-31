#include "instanced.h"

#include "layer.h"

#include <glm/gtc/type_ptr.hpp>

namespace drawable
{
namespace renderer
{
Instanced::Instanced(Shader* shader, glm::mat4 transform)
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
        m_vbo.useVertexAttrib(static_cast<uint32_t>(model + 0), 4, GL_FLOAT, false, sizeof(Vertex), 0 * sizeof(glm::vec4) + offsetof(Vertex, model), true);
        m_vbo.useVertexAttrib(static_cast<uint32_t>(model + 1), 4, GL_FLOAT, false, sizeof(Vertex), 1 * sizeof(glm::vec4) + offsetof(Vertex, model), true);
        m_vbo.useVertexAttrib(static_cast<uint32_t>(model + 2), 4, GL_FLOAT, false, sizeof(Vertex), 2 * sizeof(glm::vec4) + offsetof(Vertex, model), true);
        m_vbo.useVertexAttrib(static_cast<uint32_t>(model + 3), 4, GL_FLOAT, false, sizeof(Vertex), 3 * sizeof(glm::vec4) + offsetof(Vertex, model), true);
    }
}

void Instanced::submit(const int& numVerts, Vertex* vertices, const int& numIndices, GLint* indices)
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

bool Instanced::submit(DrawableObject* object)
{
    Texture* objectTexture = object->getTexture();
    if(objectTexture)
    {
        m_textures.clear();
        m_textures.push_back(objectTexture);
        object->setTextureId(static_cast<int>(m_textures.size()));
    }

    m_objects.clear();
    m_vertices.clear();
    m_indices.clear();
    m_objects.push_back(std::make_pair(object, m_vertices.size()));
    submit(object->numVerts(), object->verts(), object->numIndices(), object->indices());

    m_changed = true;

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

void Instanced::draw(glm::mat4 transform)
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
        m_shader->setUniform("textures", static_cast<int>(m_textures.size()), &data.front());
    }

    if(m_changed)
    {
        m_ibo.buffer(static_cast<long>(m_indices.size() * sizeof(GLint)), reinterpret_cast<void*>(&m_indices.front()));
        m_vbo.buffer(static_cast<long>(m_vertices.size() * sizeof(Vertex)), reinterpret_cast<void*>(&m_vertices.front()));
        m_changed = false;

        glGenBuffers(1, &test);
        glBindBuffer(GL_ARRAY_BUFFER, test);
        glBufferData(GL_ARRAY_BUFFER, m_transforms.size() * static_cast<long>(sizeof(glm::mat4)), &m_transforms[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(4);
        glEnableVertexAttribArray(5);
        glEnableVertexAttribArray(6);
        glEnableVertexAttribArray(7);

        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), reinterpret_cast<void*>(0 * sizeof(glm::vec4)));
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), reinterpret_cast<void*>(1 * sizeof(glm::vec4)));
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), reinterpret_cast<void*>(2 * sizeof(glm::vec4)));
        glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), reinterpret_cast<void*>(3 * sizeof(glm::vec4)));

        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);
        glVertexAttribDivisor(7, 1);
    }

    m_ibo.bind();
    m_vbo.bind();
    glBindBuffer(GL_ARRAY_BUFFER, test);
    glEnableVertexAttribArray(4);
    glEnableVertexAttribArray(5);
    glEnableVertexAttribArray(6);
    glEnableVertexAttribArray(7);

    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), reinterpret_cast<void*>(0 * sizeof(glm::vec4)));
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), reinterpret_cast<void*>(1 * sizeof(glm::vec4)));
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), reinterpret_cast<void*>(2 * sizeof(glm::vec4)));
    glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), reinterpret_cast<void*>(3 * sizeof(glm::vec4)));

    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);
    glVertexAttribDivisor(7, 1);

    glDrawElementsInstanced(m_drawType, static_cast<int>(m_indices.size()), GL_UNSIGNED_INT, nullptr, m_transforms.size());
}

void Instanced::submit(const glm::mat4& transform)
{
    m_transforms.push_back(transform);
    m_changed = true;
}

}
}
