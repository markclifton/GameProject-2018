#include "indexbuffer.h"

namespace ps
{
namespace buffers
{
IndexBuffer::IndexBuffer()
{
    glGenBuffers(1, &m_ibo);
}

IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
}

void IndexBuffer::buffer(const long& totalSize, void* indices, const unsigned int& type)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, totalSize, indices, type);
}
}
}
