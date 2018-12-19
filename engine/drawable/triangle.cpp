#include "triangle.h"

#include <glm/gtc/type_ptr.hpp>

#include "buffers/indexbuffer.h"
#include "buffers/vertexbuffer.h"

namespace ps
{
namespace drawable
{
Triangle::Triangle(glm::vec3 center, Shader* shader)
    : DrawableEntity (shader)
{
    m_indices.push_back(0);
    m_indices.push_back(2);
    m_indices.push_back(1);

    float size = .0625f / 4.f;
    VertexComponent v1, v2, v3;
    v1.pos = glm::vec3(center.x - size, center.y - size, center.z);
    v1.color = glm::vec4(1,0,0,1);
    v1.uv = glm::vec3(0,0,-1);

    v2.pos = glm::vec3(center.x, center.y + size, center.z);
    v2.color = glm::vec4(0,1,0,1);
    v2.uv = glm::vec3(0,0,-1);

    v3.pos = glm::vec3(center.x + size, center.y - size, center.z);
    v3.color = glm::vec4(0,0,1,1);
    v3.uv = glm::vec3(0,0,-1);

    addVertex(v1);
    addVertex(v2);
    addVertex(v3);
}
}
}
