#pragma once

#include <glm/matrix.hpp>

#include <vector>

#include "managers/texturemanager.h"
#include "shaders/shader.h"

namespace ps
{
namespace drawable
{
//TODO: Remove "inlines" from header
// Drawable can have a draw called upon it
class Drawable
{
public:
    Drawable(Shader* shader) : m_shader( shader ) {}
    virtual ~Drawable() = default;
    virtual void draw(glm::mat4 transform = glm::mat4(1.f)) = 0;

    virtual void setTransform(glm::mat4 transform)
    {
        m_transform = transform;
    }

    inline Shader* getShader() { return m_shader; }
    inline void setDrawType(const uint32_t& type) { m_drawType = type; }

protected:
    Shader* m_shader;
    glm::mat4 m_transform {1.f};
    uint32_t m_drawType {GL_TRIANGLES};
};
}
}
