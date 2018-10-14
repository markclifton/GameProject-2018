#pragma once

#include <GL/glew.h>
#include <glm/vec3.hpp>

#include "drawable.h"
#include "drawablebasics.h"

namespace drawable
{
    class Rectangle : public Drawable
    {
    public:
        Rectangle(glm::vec3 center, Shader* shader);

        void draw(glm::mat4 transform = glm::mat4(1.f)) override;

        Vertex m_vertices[4];
        GLint m_indices[6];
    };
}
