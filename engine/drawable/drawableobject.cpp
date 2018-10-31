#include "drawableobject.h"

namespace drawable
{
DrawableObject::DrawableObject(Shader* shader) : Drawable( shader )
{
    shader->bind();

    int position = shader->getAttribLocation("position");
    if(position >= 0)
    {
        m_vertexBuffer.useVertexAttrib(static_cast<uint32_t>(position), 3, GL_FLOAT, false, sizeof(Vertex), offsetof(Vertex, pos));
    }

    int color = shader->getAttribLocation("color");
    if(color >= 0)
    {
        m_vertexBuffer.useVertexAttrib(static_cast<uint32_t>(color), 4, GL_FLOAT, false, sizeof(Vertex), offsetof(Vertex, color));
    }

    int uv = shader->getAttribLocation("uv");
    if(uv >= 0)
    {
        m_vertexBuffer.useVertexAttrib(static_cast<uint32_t>(uv), 3, GL_FLOAT, false, sizeof(Vertex), offsetof(Vertex, uv));
    }

    int normal = shader->getAttribLocation("normal");
    if(normal >= 0)
    {
        m_vertexBuffer.useVertexAttrib(static_cast<uint32_t>(normal), 3, GL_FLOAT, false, sizeof(Vertex), offsetof(Vertex, normal));
    }

    int model = shader->getAttribLocation("model");
    if(model >= 0)
    {
        m_vertexBuffer.useVertexAttrib(static_cast<uint32_t>(model + 0), 4, GL_FLOAT, false, sizeof(Vertex), 0 * sizeof(glm::vec4) + offsetof(Vertex, model));
        m_vertexBuffer.useVertexAttrib(static_cast<uint32_t>(model + 1), 4, GL_FLOAT, false, sizeof(Vertex), 1 * sizeof(glm::vec4) + offsetof(Vertex, model));
        m_vertexBuffer.useVertexAttrib(static_cast<uint32_t>(model + 2), 4, GL_FLOAT, false, sizeof(Vertex), 2 * sizeof(glm::vec4) + offsetof(Vertex, model));
        m_vertexBuffer.useVertexAttrib(static_cast<uint32_t>(model + 3), 4, GL_FLOAT, false, sizeof(Vertex), 3 * sizeof(glm::vec4) + offsetof(Vertex, model));
    }
}

void DrawableObject::setTransform(glm::mat4 transform)
{
    m_transform = transform;
    for(auto& vert : m_vertices)
    {
        vert.model = m_transform;
    }
    update();
}

void DrawableObject::setTextureId(const int& id)
{
    for(auto& vert : m_vertices)
    {
        vert.uv.z = id;
    }
    update();
}

void DrawableObject::setColor(const glm::vec4& color)
{
    for(auto& vertex : m_vertices)
    {
        vertex.color = color;
    }
    update();
}

void DrawableObject::setUpdateFunc(std::function<void()> fn)
{
    m_updateFunc = fn;
}

void DrawableObject::update()
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

const bbox& DrawableObject::calculateBBox()
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

void DrawableObject::calculateNormals()
{
    for(size_t i = 0; i<m_indices.size(); i+=3)
    {
        auto& vert1 = m_vertices[static_cast<size_t>(m_indices[i+0])];
        auto& vert2 = m_vertices[static_cast<size_t>(m_indices[i+1])];
        auto& vert3 = m_vertices[static_cast<size_t>(m_indices[i+2])];

        auto edge1 = vert2.pos - vert1.pos;
        auto edge2 = vert3.pos - vert1.pos;

        auto normal = glm::normalize(glm::cross(edge1, edge2));

        vert1.normal += normal;
        vert2.normal += normal;
        vert3.normal += normal;
    }
}

void DrawableObject::setInstanced()
{
    m_shader->bind();
    int model = m_shader->getAttribLocation("model");
    if(model >= 0)
    {
        m_vertexBuffer.useVertexAttrib(static_cast<uint32_t>(model + 0), 4, GL_FLOAT, false, sizeof(Vertex), 0 * sizeof(glm::vec4) + offsetof(Vertex, model), true);
        m_vertexBuffer.useVertexAttrib(static_cast<uint32_t>(model + 1), 4, GL_FLOAT, false, sizeof(Vertex), 1 * sizeof(glm::vec4) + offsetof(Vertex, model), true);
        m_vertexBuffer.useVertexAttrib(static_cast<uint32_t>(model + 2), 4, GL_FLOAT, false, sizeof(Vertex), 2 * sizeof(glm::vec4) + offsetof(Vertex, model), true);
        m_vertexBuffer.useVertexAttrib(static_cast<uint32_t>(model + 3), 4, GL_FLOAT, false, sizeof(Vertex), 3 * sizeof(glm::vec4) + offsetof(Vertex, model), true);
    }
}

}
