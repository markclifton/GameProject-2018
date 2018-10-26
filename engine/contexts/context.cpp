#include "context.h"

#include <glm/gtc/matrix_transform.hpp>

#include "../drawable/triangle.h"
#include "../drawable/rectangle.h"
#include "../drawable/batchrenderer.h"

Context::Context(managers::ShaderManager& shaderManager, managers::TextureManager& textureManager)
    : m_shaderManager(shaderManager)
    , m_textureManager(textureManager)
    , m_stack(shaderManager, textureManager)
{
    loadResources();

    drawable::BatchRenderer* batch = new drawable::BatchRenderer(m_shaderManager.getShader("BasicShader"), glm::translate(glm::mat4(1.f), glm::vec3(-1,0,0)));
    for(float x=-1; x<=1.f; x+=.0625f/2.f)
    {
        for(float y=-1; y<=1.f; y+=.0625f/2.f)
        {
            batch->submit(new drawable::Triangle( glm::vec3(x,y, -1), m_shaderManager.getShader("BasicShader") )); //Memory Leak
        }
    }

    batch->setTransform(glm::translate(glm::mat4(1.f), glm::vec3(1,0,0)));

    m_stack.submit(batch);

    // Horrible assumptions are made... FIX ME
    auto shader = m_shaderManager.getShader("BasicShader");
    shader->bind();

    int data [2] {0, 1};
    shader->setUniform("myTextures", 2, data);

    drawable::Rectangle* r = new drawable::Rectangle(glm::vec3(0,0,0), shader); //Memory Leak
    r->setTexture(m_textureManager.find("smile"));
    r->setTransform(glm::translate(glm::mat4(1.f), glm::vec3(-.5f,0,0)));
    batch->submit(r);

    drawable::Rectangle* r2 = new drawable::Rectangle(glm::vec3(0,0,0), shader); //Memory Leak
    r2->setTexture(m_textureManager.find("smile2"));
    batch->submit(r2);
    r2->setTransform(glm::translate(glm::mat4(1.f), glm::vec3(.5f,0,0)));
}

void Context::run()
{
    m_stack.draw();
}

void Context::loadResources()
{
    m_textureManager.load("smile", "resources/images/smile.tif");
    m_textureManager.load("smile2", "resources/images/smile2.tif");
}
