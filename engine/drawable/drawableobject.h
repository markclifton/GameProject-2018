#pragma once

#include <functional>
#include <vector>

#include "buffers/indexbuffer.h"
#include "buffers/vertexbuffer.h"
#include "drawable.h"
#include "textures/texture.h"

#include "ecs/ientity.h"
#include "ecs/components/vertex.h"

namespace drawable
{
struct bbox
{
    glm::vec3 min {0};
    glm::vec3 max {0};
};

class DrawableObject : public drawable::Drawable, public ecs::IEntity
{
public:
    DrawableObject(Shader* shader);

    void setTransform(glm::mat4 transform) override;

    void setTextureId(const int& id);
    void setTexture( Texture* texture ) { m_texture = texture; setTextureId(0); }
    Texture* getTexture() { return m_texture; }

    Vertex* verts() { return reinterpret_cast<Vertex*>(GetComponentByTypeAndIndex(Vertex::Type, 0)); }
    int numVerts() { return static_cast<int>(NumComponentsForType(Vertex::Type)); }

    GLint* indices() { return &m_indices.front(); }
    int numIndices() { return static_cast<int>(m_indices.size()); }

    void setColor(const glm::vec4& color);

    void setUpdateFunc(std::function<void()> fn);
    void update();

    const bbox& calculateBBox(); //Diagonal Corner BBox that is Axis Aligned
    void calculateNormals();

    void setInstanced();

    inline void addVertex(Vertex& vertex) { AddComponentOfType(Vertex::Type, Vertex::CreationFN(this, &vertex)); }

protected:
    std::vector<GLint> m_indices;
    Texture* m_texture {nullptr};

    buffers::VertexBuffer m_vertexBuffer;
    buffers::IndexBuffer m_indicesBuffer;
    bool m_changed { true };

    std::function<void()> m_updateFunc;

    bbox m_bbox;
};
}
