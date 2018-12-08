#pragma once

#include "glm/matrix.hpp"

#include "ecs/components/vertex.h"
#include "drawable/drawableobject.h"
#include "ecs/isystem.h"

#include "shaders/shader.h"

#include <iostream>

namespace ecs
{

class RendererSystem : public ISystem
{
public:
    RendererSystem()
    {
        components_.push_back(Vertex::Type);
    }

    void update(float, void** component) override
    {
        auto vertComponent = reinterpret_cast<Vertex*>(*component);
        auto entity = reinterpret_cast<drawable::DrawableObject*>(vertComponent->entityHandle);

        if(entity == nullptr)
        {
            return;
        }

        size_t numVerts = static_cast<size_t>(entity->NumComponentsForType(Vertex::Type));
        if(entity->shader_ != nullptr)
        {
            //entity->shader_->bind();
            entity->shader_->setUniform("transform", glm::mat4(1.f));
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
            entity->m_vertexBuffer.buffer(static_cast<long>(numVerts*sizeof(Vertex)), entity->verts());
        }

        glDrawElements(GL_TRIANGLES, static_cast<int>(entity->m_indices.size()), GL_UNSIGNED_INT, nullptr);
    }
};

}
