#pragma once

#include "glad/gl.h"

#include <vector>

namespace buffers
{
struct VertexAttrib
{
    uint32_t vertexPosition;
    int count;
    uint32_t type; // e.g. GL_FLOAT, GL_INT
    bool normalized;
    int stride;
    uint32_t offset;
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
    void useVertexAttrib(uint32_t vertexPosition, int count, uint32_t type, bool normalized, int stride, uint32_t offset, bool instanced = false);
    void useVertexAttribDivisor(uint32_t vertexPosition);
private:
    GLuint m_vbo;

    std::vector<VertexAttrib> m_vertexAttribs;
    std::vector<uint32_t> m_vertexAttribDivisors;
};
}
