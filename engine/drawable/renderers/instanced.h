#pragma once

#include <functional>
#include <vector>

#include "buffers/indexbuffer.h"
#include "buffers/vertexbuffer.h"
#include "drawable/drawable.h"
#include "drawable/drawablebasics.h"
#include "drawable/drawableobject.h"

namespace drawable
{
namespace renderer
{
class Instanced : public Drawable
{
public:
    Instanced(Shader *shader, glm::mat4 transform = glm::mat4(1.f));

    void submit(const int& numVerts,  Vertex* vertices, const int& numIndices, GLint* indices);
    bool submit(DrawableObject* object);
    void draw(glm::mat4 transform = glm::mat4(1.f)) override;

    inline const std::vector<Texture*>& getTextures() { return m_textures; }

    void submit(const glm::mat4& transform);

private:
    std::vector<Vertex> m_vertices;
    std::vector<GLint> m_indices;

    std::vector<std::pair<DrawableObject*, size_t>> m_objects; //TODO: Enable remove of objects
    std::vector<Texture*> m_textures;

    buffers::VertexBuffer m_vboTransforms;
    buffers::VertexBuffer m_vbo;
    buffers::IndexBuffer m_ibo;

    glm::mat4 m_tranform {1.f};
    std::vector<glm::mat4> m_transforms;
    bool m_changed { true };
};

}
}
