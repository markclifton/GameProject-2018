#pragma once

#include <functional>
#include <vector>

#include "buffers/indexbuffer.h"
#include "buffers/vertexbuffer.h"
#include "drawable.h"
#include "drawablebasics.h"
#include "textures/texture.h"

namespace drawable
{
struct bbox
{
    glm::vec3 min {0};
    glm::vec3 max {0};
};

class DrawableObject : public drawable::Drawable
{
public:
    DrawableObject(Shader* shader);

    void setTransform(glm::mat4 transform) override;

    void setTextureId(const int& id);
    void setTexture( Texture* texture ) { m_texture = texture; setTextureId(0); }
    Texture* getTexture() { return m_texture; }

    Vertex* verts() { return &m_vertices.front(); }
    int numVerts() { return static_cast<int>(m_vertices.size()); }

    GLint* indices() { return &m_indices.front(); }
    int numIndices() { return static_cast<int>(m_indices.size()); }

    void setColor(const glm::vec4& color);

    void setUpdateFunc(std::function<void()> fn);
    void update();

    const bbox& calculateBBox(); //Diagonal Corner BBox that is Axis Aligned
    void calculateNormals();

    void setInstanced();

protected:
    std::vector<Vertex> m_vertices;
    std::vector<GLint> m_indices;
    Texture* m_texture {nullptr};

    buffers::VertexBuffer m_vertexBuffer;
    buffers::IndexBuffer m_indicesBuffer;
    bool m_changed { true };

    std::function<void()> m_updateFunc;

    bbox m_bbox;
};
}
