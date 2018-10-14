#pragma once

#include "glm/vec3.hpp"
#include "glm/matrix.hpp"

namespace drawable
{
    struct Vertex
    {
        Vertex(){}
        Vertex(glm::vec3 color, glm::vec3 pos)
            : color(color), pos(pos)
        {}
        glm::vec3 color;
        glm::vec3 pos;
    };
}
