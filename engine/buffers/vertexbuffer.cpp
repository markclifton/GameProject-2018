#include "vertexbuffer.h"
#include <iostream>
namespace buffers
{
    VertexBuffer::VertexBuffer()
    {
        glGenBuffers(1, &m_vbo);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &m_vbo);
    }

    void VertexBuffer::bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        setAttribPointers();
    }

    void VertexBuffer::buffer(const long& totalSize, void* data, const unsigned int& drawType)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, totalSize, data, drawType);

        setAttribPointers();
    }
}
