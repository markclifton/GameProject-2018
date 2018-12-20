#pragma once

#include "glad/gl.h"

namespace ps
{
namespace buffers
{
class IndexBuffer
{
public:
    IndexBuffer();
    ~IndexBuffer();

    void bind();
    void buffer(const long& totalSize, void* indices, const unsigned int& type = GL_STATIC_DRAW);

    inline void release()
    {
        if(m_ibo != 0)
        {
            glDeleteBuffers(1, &m_ibo);
            m_ibo = 0;
        }
    }

private:
    IndexBuffer(IndexBuffer const&) = delete;
    void operator=(IndexBuffer const&) = delete;

    GLuint m_ibo;
};
}
}
