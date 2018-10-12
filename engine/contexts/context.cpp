#include "context.h"

#include "../drawable/triangle.h"

Context::Context()
{
}

void Context::run()
{
    for(float x=-1; x<=1.f; x+=.5f)
    {
        for(float y=-1; y<=1.f; y+=.5f)
        {
            Triangle( (glm::vec3(x,y, 0)) ).draw();
        }
    }
}
