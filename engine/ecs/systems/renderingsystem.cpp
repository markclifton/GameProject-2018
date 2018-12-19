#include "renderingsystem.h"

#include "glm/matrix.hpp"

#include <algorithm>
#include <iostream>

#include "shaders/shader.h"

#include "ecs/entities/drawableentity.h"
#include "ecs/components/batchedcomponent.h"
#include "ecs/components/instancedcomponent.h"

namespace ps
{
namespace ecs
{
RenderingSystem::RenderingSystem()
{
    components_.push_back(VertexComponent::Type);
    components_.push_back(ShaderComponent::Type);
}

void RenderingSystem::update(std::vector<COMP_TYPE> componentsToUse, float, void** component)
{
    auto baseComponent = reinterpret_cast<BaseComponent*>(*component);
    auto entity = reinterpret_cast<drawable::DrawableEntity*>(baseComponent->entityHandle);
    if( entity == nullptr
            || entity->GetComponentByTypeAndIndex(BatchedComponent::Type, 0)
            || entity->GetComponentByTypeAndIndex(InstancedComponent::Type, 0) )
    {
        return;
    }


    auto useShader = (std::find(componentsToUse.begin(), componentsToUse.end(), ShaderComponent::Type) != componentsToUse.end());
    auto shaderComponent = reinterpret_cast<ShaderComponent*>(entity->GetComponentByTypeAndIndex(ShaderComponent::Type, 0));
    if(shaderComponent != nullptr && useShader)
    {
        shaderComponent->shader->bind();
        shaderComponent->shader->setUniform("transform", glm::mat4(1.f));

        auto textureComp = reinterpret_cast<TextureComponent*>(entity->GetComponentByTypeAndIndex(TextureComponent::Type, 0));
        if( textureComp )
        {
            std::vector<int> data {0};
            shaderComponent->shader->setUniform("textures", static_cast<int>(data.size()), &data.front());
            textureComp->texture->bind(0);
        }
    }

    entity->m_indicesBuffer.bind();
    entity->m_vertexBuffer.bind();

    if(entity->m_changed)
    {
        entity->m_changed = false;
        entity->m_indicesBuffer.buffer(static_cast<long>(entity->m_indices.size()*sizeof(GLint)), reinterpret_cast<void*>(&entity->m_indices.front()));

        size_t numVerts = static_cast<size_t>(entity->NumComponentsForType(VertexComponent::Type));
        entity->m_vertexBuffer.buffer(static_cast<long>(numVerts*sizeof(VertexComponent)), entity->verts());
    }

    glDrawElements(GL_TRIANGLES, static_cast<int>(entity->m_indices.size()), GL_UNSIGNED_INT, nullptr);
}
}
}
