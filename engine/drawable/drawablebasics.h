#pragma once

#include "glm/vec3.hpp"

struct vertex
{
    vertex(){}
    vertex(glm::vec3 color, glm::vec3 pos)
        : color(color), pos(pos)
    {}
    glm::vec3 color;
    glm::vec3 pos;
};
