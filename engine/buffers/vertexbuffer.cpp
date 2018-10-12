#include "vertexbuffer.h"

VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, & m_vbo);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_vbo);
}

void VertexBuffer::buffer(const long& totalSize, void* verts, const unsigned int& drawType)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, totalSize, verts, drawType);

    setAttribPointers();
}

void VertexBuffer::setAttribPointers()
{
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
}
