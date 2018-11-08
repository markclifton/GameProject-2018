#include "rectangle.h"

#include <glm/gtc/type_ptr.hpp>

#include "buffers/indexbuffer.h"
#include "buffers/vertexbuffer.h"

namespace drawable
{
Rectangle::Rectangle(glm::vec3 center, Shader* shader)
    : DrawableObject (shader)
{
    m_indices.push_back(0);
    m_indices.push_back(2);
    m_indices.push_back(1);
    m_indices.push_back(0);
    m_indices.push_back(3);
    m_indices.push_back(2);

    float size = 1.f;
    Vertex v1, v2, v3, v4;
    v1.color = glm::vec4(1,0,0,1);
    v1.pos = glm::vec3(center.x - size, center.y - size, center.z);
    v1.uv = glm::vec3(0,0,-1);

    v2.color = glm::vec4(0,1,0,1);
    v2.pos = glm::vec3(center.x - size, center.y + size, center.z);
    v2.uv = glm::vec3(0,1,-1);

    v3.color = glm::vec4(0,0,1,1);
    v3.pos = glm::vec3(center.x + size, center.y + size, center.z);
    v3.uv = glm::vec3(1,1,-1);

    v4.color = glm::vec4(1,0,1,1);
    v4.pos = glm::vec3(center.x + size, center.y - size, center.z);
    v4.uv = glm::vec3(1,0,-1);

    m_vertices.push_back(v1);
    m_vertices.push_back(v2);
    m_vertices.push_back(v3);
    m_vertices.push_back(v4);
}

void Rectangle::draw(glm::mat4 transform)
{
    if(m_shader != nullptr)
    {
       // m_shader->bind();
        m_shader->setUniform("transform", transform);
    }

    if(m_texture)
    {
        m_texture->bind(0);
    }

    m_indicesBuffer.bind();
    m_vertexBuffer.bind();
    if(m_changed)
    {
        m_changed = false;
        m_indicesBuffer.buffer(static_cast<long>(m_indices.size()*sizeof(GLint)), reinterpret_cast<void*>(&m_indices.front()));
        m_vertexBuffer.buffer(static_cast<long>(m_vertices.size()*sizeof(Vertex)), reinterpret_cast<void*>(&m_vertices.front()));
    }

    glDrawElements(m_drawType, static_cast<int>(m_indices.size()), GL_UNSIGNED_INT, nullptr);
}
}
