#include "triangle.h"

#include <glm/gtc/type_ptr.hpp>

#include "buffers/indexbuffer.h"
#include "buffers/vertexbuffers/vb_basic.h"

namespace drawable
{
    Triangle::Triangle(glm::vec3 center, Shader* shader)
        : Drawable(shader)
    {
        float size = .0625f / 4.f;

        m_indices[0] = 0;
        m_indices[1] = 1;
        m_indices[2] = 2;

        m_vertices[0].pos = glm::vec3(center.x - size, center.y - size, center.z);
        m_vertices[1].pos = glm::vec3(center.x, center.y + size, center.z);
        m_vertices[2].pos = glm::vec3(center.x + size, center.y - size, center.z);

        m_vertices[0].color = glm::vec4(1,0,0,1);
        m_vertices[1].color = glm::vec4(0,1,0,1);
        m_vertices[2].color = glm::vec4(0,0,1,1);
    }

    void Triangle::draw(glm::mat4 transform)
    {
        if(m_shader != nullptr)
        {
            m_shader->bind();
            m_shader->setUniform("transform", transform);
        }

        // TODO: FIX ME (Not Needed)
        buffers::IndexBuffer i;
        i.buffer(sizeof(m_indices), reinterpret_cast<void*>(m_indices));

        // TODO: FIX ME (Not Needed)
        buffers::BasicVBO v;
        v.buffer(sizeof(m_vertices), reinterpret_cast<void*>(m_vertices));

        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
    }
}
