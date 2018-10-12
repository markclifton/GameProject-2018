#pragma once

#include <GL/glew.h>

#include "drawablebasics.h"

class Triangle
{
public:
    Triangle(position center);

    void draw();
private:
    position m_vertices[3];
    GLint m_indices[3];
};
