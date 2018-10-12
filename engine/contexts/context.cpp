#include "context.h"

#include "../drawable/triangle.h"

Context::Context()
{
    for(float x=-1; x<=1.f; x+=.0625f/2.f)
    {
        for(float y=-1; y<=1.f; y+=.0625f/2.f)
        {
            Triangle t( (glm::vec3(x,y, 0)) );
            m_batch.submit(3, t.m_vertices, 3, t.m_indices);
        }
    }
}

void Context::run()
{
    m_batch.draw();
}
