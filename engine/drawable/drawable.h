#pragma once

#include <glm/matrix.hpp>

#include "../shaders/shader.h"

namespace drawable
{
    class Drawable
    {
    public:
        Drawable(Shader* shader) : m_shader( shader ) {}
        virtual ~Drawable() = default;
        virtual void draw(glm::mat4 transform = glm::mat4(1.f)) = 0;

        inline void setTransform(glm::mat4 transform) { m_transform = transform; }

    protected:
        glm::mat4 m_transform {1.f};
        Shader* m_shader;
    };
}
