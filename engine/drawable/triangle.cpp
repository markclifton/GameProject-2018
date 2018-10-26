#include "triangle.h"

#include <glm/gtc/type_ptr.hpp>

#include "buffers/indexbuffer.h"
#include "buffers/vertexbuffers/vb_basic.h"

namespace drawable
{
    Triangle::Triangle(glm::vec3 center, Shader* shader)
        : DrawableObject (shader)
    {
        m_indices.push_back(0);
        m_indices.push_back(1);
        m_indices.push_back(2);

        float size = .0625f / 4.f;
        Vertex v1, v2, v3;
        v1.pos = glm::vec3(center.x - size, center.y - size, center.z);
        v1.color = glm::vec4(1,0,0,1);
        v1.uv = glm::vec3(0,0,-1);

        v2.pos = glm::vec3(center.x, center.y + size, center.z);
        v2.color = glm::vec4(0,1,0,1);
        v2.uv = glm::vec3(0,0,-1);

        v3.pos = glm::vec3(center.x + size, center.y - size, center.z);
        v3.color = glm::vec4(0,0,1,1);
        v3.uv = glm::vec3(0,0,-1);

        m_vertices.push_back(v1);
        m_vertices.push_back(v2);
        m_vertices.push_back(v3);
    }

    void Triangle::draw(glm::mat4 transform)
    {
        if(m_shader != nullptr)
        {
            m_shader->bind();
            m_shader->setUniform("transform", transform);
        }

        if(m_texture)
        {
            m_texture->bind(0);
        }

        // TODO: FIX ME (Not Needed)
        buffers::IndexBuffer i;
        i.buffer(static_cast<long>(m_indices.size()*sizeof(GLint)), reinterpret_cast<void*>(&m_indices.front()));

        // TODO: FIX ME (Not Needed)
        buffers::BasicVBO v;
        v.buffer(static_cast<long>(m_vertices.size()*sizeof(Vertex)), reinterpret_cast<void*>(&m_vertices.front()));

        glDrawElements(GL_TRIANGLES, static_cast<int>(m_indices.size()), GL_UNSIGNED_INT, nullptr);
    }
}
