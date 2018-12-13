#pragma once

#include <functional>
#include <vector>

#include "buffers/indexbuffer.h"
#include "buffers/vertexbuffer.h"
#include "textures/texture.h"

#include "ecs/ientity.h"
#include "ecs/entities/drawableentity.h"
#include "ecs/components/shadercomponent.h"
#include "ecs/components/texturecomponent.h"
#include "ecs/components/vertexcomponent.h"

namespace drawable
{
struct bbox
{
    glm::vec3 min {0};
    glm::vec3 max {0};
};

class DrawableEntity : public ecs::IEntity
{
public:
    DrawableEntity(Shader* shader);

    void setTextureId(const int& id);
    void setTexture( Texture* texture )
    {
        TextureComponent texComp;
        texComp.texture = texture;
        AddComponentOfType(TextureComponent::Type, TextureComponent::CreationFN(this, &texComp));
        setTextureId(1);
    }
    Texture* getTexture() { return reinterpret_cast<TextureComponent*>(GetComponentByTypeAndIndex(TextureComponent::Type, 0))->texture; }

    VertexComponent* verts() { return reinterpret_cast<VertexComponent*>(GetComponentByTypeAndIndex(VertexComponent::Type, 0)); }
    int numVerts() { return static_cast<int>(NumComponentsForType(VertexComponent::Type)); }

    GLint* indices() { return &m_indices.front(); }
    int numIndices() { return static_cast<int>(m_indices.size()); }

    void setColor(const glm::vec4& color);

    void setUpdateFunc(std::function<void()> fn);
    void update();

    const bbox& calculateBBox(); //Diagonal Corner BBox that is Axis Aligned
    void calculateNormals();

    void setInstanced();
    void setBatched();

    inline void addVertex(VertexComponent& vertex) { AddComponentOfType(VertexComponent::Type, VertexComponent::CreationFN(this, &vertex)); }
    inline void setShader(ShaderComponent& shader) { AddComponentOfType(ShaderComponent::Type, ShaderComponent::CreationFN(this, &shader)); }

    void setTransform(glm::mat4 transform);

public:
    std::vector<GLint> m_indices;
    glm::mat4 m_transform {1.f};

    buffers::VertexBuffer m_vertexBuffer;
    buffers::IndexBuffer m_indicesBuffer;
    bool m_changed { true };

    std::function<void()> m_updateFunc;

    bbox m_bbox;
};
}
