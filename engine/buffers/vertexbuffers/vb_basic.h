#pragma once

#include "../../drawable/drawablebasics.h"
#include "../vertexbuffer.h"

namespace buffers
{
    class BasicVBO : public VertexBuffer
    {
    public:
        inline void setAttribPointers() override
        {
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(drawable::Vertex), reinterpret_cast<void*>(offsetof(drawable::Vertex, pos)));
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(drawable::Vertex), reinterpret_cast<void*>(offsetof(drawable::Vertex, color)));
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(drawable::Vertex), reinterpret_cast<void*>(offsetof(drawable::Vertex, uv)));
        }
    };
}
