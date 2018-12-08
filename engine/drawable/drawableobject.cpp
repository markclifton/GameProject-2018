#include "drawableobject.h"

#include <algorithm>

namespace drawable
{
DrawableObject::DrawableObject(Shader* shader)
{
    ShaderComponent shaderComp;
    shaderComp.shader = shader;
    setShader(shaderComp);

    //Vertex is no longer a pod, and therefore offsetof cannot be "used" (Undefined Behaviour, rip...)
    //tbd...
    int position = shader->getAttribLocation("position");
    if(position >= 0)
    {
        m_vertexBuffer.useVertexAttrib(static_cast<uint32_t>(position), 3, GL_FLOAT, false, sizeof(VertexComponent), offsetof(VertexComponent, pos));
    }

    int color = shader->getAttribLocation("color");
    if(color >= 0)
    {
        m_vertexBuffer.useVertexAttrib(static_cast<uint32_t>(color), 4, GL_FLOAT, false, sizeof(VertexComponent), offsetof(VertexComponent, color));
    }

    int uv = shader->getAttribLocation("uv");
    if(uv >= 0)
    {
        m_vertexBuffer.useVertexAttrib(static_cast<uint32_t>(uv), 3, GL_FLOAT, false, sizeof(VertexComponent), offsetof(VertexComponent, uv));
    }

    int normal = shader->getAttribLocation("normal");
    if(normal >= 0)
    {
        m_vertexBuffer.useVertexAttrib(static_cast<uint32_t>(normal), 3, GL_FLOAT, false, sizeof(VertexComponent), offsetof(VertexComponent, normal));
    }

    int model = shader->getAttribLocation("model");
    if(model >= 0)
    {
        m_vertexBuffer.useVertexAttrib(static_cast<uint32_t>(model + 0), 4, GL_FLOAT, false, sizeof(VertexComponent), 0 * sizeof(glm::vec4) + offsetof(VertexComponent, model));
        m_vertexBuffer.useVertexAttrib(static_cast<uint32_t>(model + 1), 4, GL_FLOAT, false, sizeof(VertexComponent), 1 * sizeof(glm::vec4) + offsetof(VertexComponent, model));
        m_vertexBuffer.useVertexAttrib(static_cast<uint32_t>(model + 2), 4, GL_FLOAT, false, sizeof(VertexComponent), 2 * sizeof(glm::vec4) + offsetof(VertexComponent, model));
        m_vertexBuffer.useVertexAttrib(static_cast<uint32_t>(model + 3), 4, GL_FLOAT, false, sizeof(VertexComponent), 3 * sizeof(glm::vec4) + offsetof(VertexComponent, model));
    }
}

void DrawableObject::setTransform(glm::mat4 transform)
{
    m_transform = transform;
    for(int i=0 ; i<numVerts(); i++)
    {
        verts()[i].model = m_transform;
    }
    update();
}

void DrawableObject::setTextureId(const int& id)
{
    for(int i=0 ; i<numVerts(); i++)
    {
        verts()[i].uv.z = float(id);
    }
    update();
}

void DrawableObject::setColor(const glm::vec4& color)
{
    for(int i=0 ; i<numVerts(); i++)
    {
        verts()[i].color = color;
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
    for(int i=0 ; i<numVerts(); i++)
    {
        m_bbox.min.x = std::min(m_bbox.min.x, verts()[i].pos.x);
        m_bbox.min.y = std::min(m_bbox.min.y, verts()[i].pos.y);
        m_bbox.min.z = std::min(m_bbox.min.z, verts()[i].pos.z);
        m_bbox.max.x = std::max(m_bbox.max.x, verts()[i].pos.x);
        m_bbox.max.y = std::max(m_bbox.max.y, verts()[i].pos.y);
        m_bbox.max.z = std::max(m_bbox.max.z, verts()[i].pos.z);
    }

    return m_bbox;
}

void DrawableObject::calculateNormals()
{
    for(size_t i = 0; i<m_indices.size(); i+=3)
    {
        auto& vert1 = verts()[static_cast<size_t>(m_indices[i+0])];
        auto& vert2 = verts()[static_cast<size_t>(m_indices[i+1])];
        auto& vert3 = verts()[static_cast<size_t>(m_indices[i+2])];

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
    auto shaderComp = reinterpret_cast<ShaderComponent*>(GetComponentByTypeAndIndex(ShaderComponent::Type, 0));
    if(shaderComp == nullptr)
    {
        return;
    }

    shaderComp->shader->bind();
    int model = shaderComp->shader->getAttribLocation("model");
    if(model >= 0)
    {
        m_vertexBuffer.useVertexAttrib(static_cast<uint32_t>(model + 0), 4, GL_FLOAT, false, sizeof(VertexComponent), 0 * sizeof(glm::vec4) + offsetof(VertexComponent, model), true);
        m_vertexBuffer.useVertexAttrib(static_cast<uint32_t>(model + 1), 4, GL_FLOAT, false, sizeof(VertexComponent), 1 * sizeof(glm::vec4) + offsetof(VertexComponent, model), true);
        m_vertexBuffer.useVertexAttrib(static_cast<uint32_t>(model + 2), 4, GL_FLOAT, false, sizeof(VertexComponent), 2 * sizeof(glm::vec4) + offsetof(VertexComponent, model), true);
        m_vertexBuffer.useVertexAttrib(static_cast<uint32_t>(model + 3), 4, GL_FLOAT, false, sizeof(VertexComponent), 3 * sizeof(glm::vec4) + offsetof(VertexComponent, model), true);
    }
}

}
