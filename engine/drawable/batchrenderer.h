#pragma once

#include <GL/glew.h>

#include <vector>

#include "../buffers/indexbuffer.h"
#include "../buffers/vertexbuffers/vb_basic.h"
#include "drawable.h"
#include "drawablebasics.h"

namespace drawable
{
    class BatchRenderer : public Drawable
    {
    public:
        BatchRenderer(Shader *shader, glm::mat4 transform = glm::mat4(1.f));

        void submit(const int& numVerts,  Vertex* vertices, const int& numIndices, GLint* indices);
        void draw(glm::mat4 transform = glm::mat4(1.f)) override;

    private:
        std::vector<Vertex> m_vertices;
        std::vector<GLint> m_indices;

        buffers::BasicVBO m_vbo;
        buffers::IndexBuffer m_ibo;

        glm::mat4 m_tranform {1.f};
        bool m_changed { true };
    };
}
