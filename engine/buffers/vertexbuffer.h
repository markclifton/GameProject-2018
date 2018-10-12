#pragma once

#include <GL/glew.h>

class VertexBuffer
{
public:
    VertexBuffer();
    virtual ~VertexBuffer();

    void bind();
    void buffer(const long& totalSize, void* verts, const unsigned int& drawType = GL_STATIC_DRAW);

protected:
    virtual void setAttribPointers();

private:
    GLuint m_vbo;
};
