#pragma once

#include <GL/glew.h>

namespace buffers
{
    class VertexBuffer
    {
    public:
        VertexBuffer();
        virtual ~VertexBuffer();

        void bind();
        void buffer(const long& totalSize, void* data, const unsigned int& drawType = GL_STATIC_DRAW);

    protected:
        virtual void setAttribPointers() = 0;

    private:
        GLuint m_vbo;
    };
}
