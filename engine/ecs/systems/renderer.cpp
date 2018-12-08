#include "renderer.h"

namespace ecs
{
RendererSystem::RendererSystem()
{
    components_.push_back(VertexComponent::Type);
    components_.push_back(ShaderComponent::Type);
}

void RendererSystem::update(std::vector<COMP_TYPE> componentsToUse, float, void** component)
{
    auto vertComponent = reinterpret_cast<VertexComponent*>(*component);
    auto entity = reinterpret_cast<drawable::DrawableObject*>(vertComponent->entityHandle);

    if(entity == nullptr)
    {
        return;
    }

    size_t numVerts = static_cast<size_t>(entity->NumComponentsForType(VertexComponent::Type));

    auto useShader = (std::find(componentsToUse.begin(), componentsToUse.end(), ShaderComponent::Type) != componentsToUse.end());
    auto shaderComponent = reinterpret_cast<ShaderComponent*>(entity->GetComponentByTypeAndIndex(ShaderComponent::Type, 0));
    if(shaderComponent != nullptr && useShader)
    {
        shaderComponent->shader->bind();
        shaderComponent->shader->setUniform("transform", glm::mat4(1.f));
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
        entity->m_vertexBuffer.buffer(static_cast<long>(numVerts*sizeof(VertexComponent)), entity->verts());
    }

    glDrawElements(GL_TRIANGLES, static_cast<int>(entity->m_indices.size()), GL_UNSIGNED_INT, nullptr);
}


}
