#include "triangle.h"

#include "../buffers/indexbuffer.h"
#include "../buffers/vertexbuffer.h"

Triangle::Triangle(position center)
{
    m_indices[0] = 0;
    m_indices[1] = 1;
    m_indices[2] = 2;

    m_vertices[0] = position(center.x - .25f, center.y - .25f);
    m_vertices[1] = position(center.x, center.y + .25f);
    m_vertices[2] = position(center.x + .25f, center.y - .25f);
}

void Triangle::draw()
{
    IndexBuffer i;
    i.buffer(sizeof(m_indices), reinterpret_cast<void*>(m_indices));

    VertexBuffer v;
    v.buffer(sizeof(m_vertices), reinterpret_cast<void*>(m_vertices));

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
}
