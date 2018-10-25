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
    drawable::BatchRenderer* batch = new drawable::BatchRenderer(m_shaderManager.getShader("BasicShader"), glm::translate(glm::mat4(1.f), glm::vec3(-1,0,0)));
    int totalObjs = 0;
    for(float x=-52; x<=52.f; x+=.0625f/2.f)
    {
        for(float y=-52; y<=52.f; y+=.0625f/2.f)
        {
            drawable::Triangle t( glm::vec3(x,y, -1), m_shaderManager.getShader("BasicShader") );
            batch->submit(3, t.m_vertices, 3, t.m_indices);
            totalObjs++;
        }
    }
    std::cout << "Total Triangles: " << totalObjs << "\n";

    batch->setTransform(glm::translate(glm::mat4(1.f), glm::vec3(1,0,0)));

    m_stack.submit(batch);

    m_textureManager.load("smile", "resources/images/smile.tif");
    m_textureManager.load("smile2", "resources/images/smile2.tif");

    // Horrible assumptions are made... FIX ME
    auto shader = m_shaderManager.getShader("BasicShader");
    shader->bind();

    int data [2] {0, 1};
    shader->setUniform("myTextures", 2, data);

    drawable::Rectangle* r = new drawable::Rectangle(glm::vec3(0,0,0), shader);
    r->setTextureName("smile");
    r->setTransform(glm::translate(glm::mat4(1.f), glm::vec3(-.5f,0,0)));
    batch->submit(r);

    drawable::Rectangle* r2 = new drawable::Rectangle(glm::vec3(0,0,0), shader);
    r2->setTextureName("smile2");
    auto fn = batch->submit(r2);

    // TEST
    r2->setTransform(glm::translate(glm::mat4(1.f), glm::vec3(.5f,0,0)));
    fn();
}

void Context::run()
{
    m_stack.draw();
}
