#pragma once

#include <GL/glew.h>
#include <glm/vec3.hpp>

#include "drawablebasics.h"

class Triangle
{
public:
    Triangle(glm::vec3 center);

    void draw();

    //temp
    Vertex m_vertices[3];
    GLint m_indices[3];
};
