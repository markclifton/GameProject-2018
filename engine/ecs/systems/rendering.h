#pragma once

#include "glm/matrix.hpp"

#include "ecs/components/vertex.h"
#include "drawable/drawableobject.h"
#include "ecs/isystem.h"

#include "shaders/shader.h"

namespace ecs
{

class RenderingSystem
{
public:
    void update(bool useShader = true, glm::mat4 transform = glm::mat4(1.f))
    {
        size_t currentOffset = 0;
        while(currentOffset < Vertex::componentTotalOffset)
        {
            auto component = reinterpret_cast<Vertex*>(Vertex::componentZero + currentOffset);
            auto entity = reinterpret_cast<drawable::DrawableObject*>(component->entityHandle);
            if(entity == nullptr)
            {
                currentOffset += sizeof(Vertex);
                continue;
            }

            auto numVerts = entity->NumComponentsForType(Vertex::Type);
            currentOffset += numVerts * sizeof(Vertex);
            if(entity->shader_ != nullptr && useShader)
            {
                entity->shader_->bind();
                entity->shader_->setUniform("transform", transform);
            }

            if(entity->m_texture)
            {
                entity->m_texture->bind(1);
            }

            entity->m_indicesBuffer.bind();
            entity->m_vertexBuffer.bind();
            if(entity->m_changed)
            {
                entity->m_changed = false;
                entity->m_indicesBuffer.buffer(static_cast<long>(entity->m_indices.size()*sizeof(GLint)), reinterpret_cast<void*>(&entity->m_indices.front()));
                entity->m_vertexBuffer.buffer(static_cast<long>(entity->numVerts()*sizeof(Vertex)), entity->verts());
            }

            glDrawElements(GL_TRIANGLES, static_cast<int>(entity->m_indices.size()), GL_UNSIGNED_INT, nullptr);
        }
    }

};

}

/*
void Triangle::draw(glm::mat4 transform)
{
    if(m_shader != nullptr)
    {
        m_shader->bind();
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
        m_vertexBuffer.buffer(static_cast<long>(numVerts()*sizeof(Vertex)), verts());
    }

    glDrawElements(m_drawType, static_cast<int>(m_indices.size()), GL_UNSIGNED_INT, nullptr);
}
*/
