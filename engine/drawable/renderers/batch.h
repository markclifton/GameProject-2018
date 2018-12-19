#pragma once

#include "glad/gl.h"
#include "glm/matrix.hpp"

#include <functional>
#include <vector>

#include "buffers/indexbuffer.h"
#include "buffers/vertexbuffer.h"
#include "drawable/drawable.h"
#include "ecs/entities/drawableentity.h"

//TODO: Broken (This is to become the Batch Rendering System)

namespace ps
{
namespace drawable
{
namespace renderer
{
class Batch : public Drawable
{
public:
    Batch(Shader *shader, glm::mat4 transform = glm::mat4(1.f));

    void submit(const int& numVerts,  VertexComponent* vertices, const int& numIndices, GLint* indices);
    bool submit(DrawableEntity* object);
    void draw(glm::mat4 transform = glm::mat4(1.f)) override;

    inline const std::vector<Texture*>& getTextures() { return m_textures; }

private:
    std::vector<VertexComponent> m_vertices;
    std::vector<GLint> m_indices;

    std::vector<std::pair<DrawableEntity*, size_t>> m_objects; //TODO: Enable remove of objects
    std::vector<Texture*> m_textures;

    buffers::VertexBuffer m_vbo;
    buffers::IndexBuffer m_ibo;

    glm::mat4 m_tranform {1.f};
    bool m_changed { true };
};
}
}
}
