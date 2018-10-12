#pragma once

#include <GL/glew.h>

class IndexBuffer
{
public:
    IndexBuffer();
    ~IndexBuffer();

    void bind();
    void buffer(const long& totalSize, void* indices, const unsigned int& type = GL_STATIC_DRAW);

private:
    GLuint m_ibo;
};
