#pragma once

#include <functional>
#include <vector>

#include "ps/buffers/indexbuffer.h"
#include "ps/buffers/vertexbuffer.h"
#include "ps/textures/texture.h"

#include "ps/ecs/ientity.h"
#include "ps/ecs/entities/drawableentity.h"
#include "ps/ecs/components/bboxcomponent.h"
#include "ps/ecs/components/shadercomponent.h"
#include "ps/ecs/components/texturecomponent.h"
#include "ps/ecs/components/vertexcomponent.h"

namespace ps
{
namespace drawable
{
class DrawableEntity : public ecs::IEntity
{
public:
    DrawableEntity(const std::string& context, Shader* shader);

    void setTextureId(const int& id);
    void setTexture( Texture* texture )
    {
        TextureComponent texComp;
        texComp.texture = texture;
        AddComponentOfType(TextureComponent::Type, TextureComponent::CreationFN(this, &texComp));
        setTextureId(1);
    }
    TextureComponent* getTexture() { return reinterpret_cast<TextureComponent*>(GetComponentByTypeAndIndex(TextureComponent::Type, 0)); }

    VertexComponent* verts() { return reinterpret_cast<VertexComponent*>(GetComponentByTypeAndIndex(VertexComponent::Type, 0)); }
    int numVerts() { return static_cast<int>(NumComponentsForType(VertexComponent::Type)); }

    GLint* indices() { return &m_indices.front(); }
    int numIndices() { return static_cast<int>(m_indices.size()); }

    void setColor(const glm::vec4& color);

    void setUpdateFunc(std::function<void()> fn);
    void update();

    BBoxComponent* calculateBBox(); //Diagonal Corner BBox that is Axis Aligned
    void calculateNormals();

    void setInstanced();
    void setBatched();

    inline void addVertex(VertexComponent& vertex) { AddComponentOfType(VertexComponent::Type, VertexComponent::CreationFN(this, &vertex)); }
    inline void setShader(ShaderComponent& shader) { AddComponentOfType(ShaderComponent::Type, ShaderComponent::CreationFN(this, &shader)); }

    void setTransform(glm::mat4 transform);
    glm::mat4 getTransform() { return m_transform; }

public:
    std::vector<GLint> m_indices;
    glm::mat4 m_transform {1.f};

    buffers::VertexBuffer m_vertexBuffer;
    buffers::IndexBuffer m_indicesBuffer;
    bool m_changed { true };

    std::function<void()> m_updateFunc;
};
}
}
