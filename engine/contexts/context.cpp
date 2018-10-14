#include "context.h"

#include <glm/gtc/matrix_transform.hpp>

#include "../drawable/triangle.h"
#include "../drawable/rectangle.h"
#include "../drawable/batchrenderer.h"

Context::Context(managers::ShaderManager& shaderManager)
    : m_shaderManager(shaderManager)
    , m_stack(m_shaderManager.getShader("BasicShader"))
{
    drawable::BatchRenderer* batch = new drawable::BatchRenderer(m_shaderManager.getShader("BasicShader"), glm::translate(glm::mat4(1.f), glm::vec3(-1,0,0)));
    for(float x=-1; x<=1.f; x+=.0625f/2.f)
    {
        for(float y=-1; y<=1.f; y+=.0625f/2.f)
        {
            drawable::Triangle t( glm::vec3(x,y, -1), m_shaderManager.getShader("BasicShader") );
            batch->submit(3, t.m_vertices, 3, t.m_indices);
        }
    }

    batch->setTransform(glm::translate(glm::mat4(1.f), glm::vec3(1,0,0)));

    m_stack.submit(batch);
    //m_stack.submit(new drawable::Rectangle(glm::vec3(0,0,0), m_shaderManager.getShader("BasicShader")));
}

void Context::run()
{
    m_stack.draw();

    drawable::Rectangle r (glm::vec3(0,0,0), m_shaderManager.getShader("BasicShader"));
    r.draw();
    r.setTransform(glm::translate(glm::mat4(1.f), glm::vec3(1,0,0)));
    r.draw();
}
