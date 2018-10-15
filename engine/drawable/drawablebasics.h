#pragma once

#include "glm/vec3.hpp"
#include "glm/matrix.hpp"

namespace drawable
{
    struct Vertex
    {
        Vertex(){}
        Vertex(glm::vec4 color, glm::vec3 pos, glm::vec3 uv = glm::vec3(0,0,0))
            : color(color), pos(pos), uv(uv)
        {}
        glm::vec4 color;
        glm::vec3 pos;
        glm::vec3 uv;
    };
}
