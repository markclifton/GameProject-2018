#pragma once

#include "../glad/gl.h"
#include <glm/vec3.hpp>

#include "drawable.h"
#include "drawablebasics.h"

namespace drawable
{
    class Triangle : public Drawable
    {
    public:
        Triangle(glm::vec3 center, Shader* shader);

        void draw(glm::mat4 transform = glm::mat4(1.f)) override;

        Vertex m_vertices[3];
        GLint m_indices[3];
    };
}
