#pragma once

#include "../../drawable/drawablebasics.h"
#include "../vertexbuffer.h"

namespace buffers
{
    class TransformVBO : public VertexBuffer
    {
    public:
        inline void setAttribPointers() override
        {
            glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));
            glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(4 * sizeof(GLfloat)));
            glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(8 * sizeof(GLfloat)));
            glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(12 * sizeof(GLfloat)));
        }
    };
}
