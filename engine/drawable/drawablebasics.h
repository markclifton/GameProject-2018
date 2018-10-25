#pragma once

#include "glm/vec3.hpp"
#include "glm/matrix.hpp"

namespace drawable
{
    struct Vertex
    {
        Vertex(){}
        Vertex(glm::vec4 color, glm::vec3 pos, glm::vec3 uv = glm::vec3(0,0,-1))
            : color(color), pos(pos), uv(uv)
        {}
        glm::vec4 color;
        glm::vec3 pos;
        glm::vec3 uv{0,0,-1};
        glm::mat4 model{1.0f};
    };
}
