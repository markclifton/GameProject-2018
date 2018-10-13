#include "triangle.h"

#include "../buffers/indexbuffer.h"
#include "../buffers/vertexbuffer.h"

Triangle::Triangle(glm::vec3 center)
{
    float size = .0625f / 4.f;

    m_indices[0] = 0;
    m_indices[1] = 1;
    m_indices[2] = 2;

    m_vertices[0].pos = glm::vec3(center.x - size, center.y - size, center.z);
    m_vertices[1].pos = glm::vec3(center.x, center.y + size, center.z);
    m_vertices[2].pos = glm::vec3(center.x + size, center.y - size, center.z);

    m_vertices[0].color = glm::vec3(1,0,0);
    m_vertices[1].color = glm::vec3(0,1,0);
    m_vertices[2].color = glm::vec3(0,0,1);
}

void Triangle::draw()
{
    IndexBuffer i;
    i.buffer(sizeof(m_indices), reinterpret_cast<void*>(m_indices));

    VertexBuffer v;
    v.buffer(sizeof(m_vertices), reinterpret_cast<void*>(m_vertices));

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
}
