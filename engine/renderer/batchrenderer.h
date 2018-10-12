#pragma once

#include <GL/glew.h>

#include <vector>

#include "../buffers/indexbuffer.h"
#include "../buffers/vertexbuffer.h"
#include "../drawable/drawablebasics.h"

class BatchRenderer
{
public:
    BatchRenderer();

    void submit(const int& numVerts,  Vertex* vertices, const int& numIndices, GLint* indices);
    void draw();

private:
    std::vector<Vertex> m_vertices;
    std::vector<GLint> m_indices;

    IndexBuffer m_ibo;
    VertexBuffer m_vbo;

    bool m_changed { true };
};
