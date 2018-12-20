#pragma once

#include "glad/gl.h"

#include <vector>

namespace ps
{
namespace buffers
{
struct VertexAttrib
{
    uint32_t vertexPosition;
    int count;
    uint32_t type; // e.g. GL_FLOAT, GL_INT
    bool normalized;
    int stride;
    size_t offset;
    bool instanced;
};

class VertexBuffer
{
public:
    VertexBuffer();
    virtual ~VertexBuffer();

    void bind();
    void buffer(const long& totalSize, void* data, const unsigned int& drawType = GL_STATIC_DRAW);

    void enableVertexAttribs();
    void useVertexAttrib(uint32_t vertexPosition, int count, uint32_t type, bool normalized, int stride, size_t offset, bool instanced = false);
    void useVertexAttribDivisor(uint32_t vertexPosition);

    inline void release()
    {
        if(m_vbo != 0)
        {
            glDeleteBuffers(1, &m_vbo);
            m_vbo = 0;
        }
    }

private:
    VertexBuffer(VertexBuffer const&) = delete;
    void operator=(VertexBuffer const&) = delete;

    GLuint m_vbo;

    std::vector<VertexAttrib> m_vertexAttribs;
    std::vector<uint32_t> m_vertexAttribDivisors;
};
}
}
