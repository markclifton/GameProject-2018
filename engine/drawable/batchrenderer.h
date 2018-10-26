#pragma once

#include "glad/gl.h"
#include "glm/matrix.hpp"

#include <functional>
#include <vector>

#include "buffers/indexbuffer.h"
#include "buffers/vertexbuffers/vb_basic.h"
#include "drawable.h"
#include "drawablebasics.h"
#include "drawableobject.h"

namespace drawable
{
    class BatchRenderer : public Drawable
    {
    public:
        BatchRenderer(Shader *shader, glm::mat4 transform = glm::mat4(1.f));

        void submit(const int& numVerts,  Vertex* vertices, const int& numIndices, GLint* indices);
        bool submit(DrawableObject* object);
        void draw(glm::mat4 transform = glm::mat4(1.f)) override;

        inline const std::vector<Texture*>& getTextures() { return m_textures; }

    private:
        std::vector<Vertex> m_vertices;
        std::vector<GLint> m_indices;

        std::vector<std::pair<DrawableObject*, size_t>> m_objects; //TODO: Enable remove of objects
        std::vector<Texture*> m_textures;

        buffers::BasicVBO m_vbo;
        buffers::IndexBuffer m_ibo;

        glm::mat4 m_tranform {1.f};
        bool m_changed { true };
    };
}
