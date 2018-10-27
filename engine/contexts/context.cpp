#include "context.h"

#include <glm/gtc/matrix_transform.hpp>

#include "drawable/triangle.h"
#include "drawable/model.h"
#include "drawable/rectangle.h"
#include "drawable/batchrenderer.h"

Context::Context(managers::ShaderManager& shaderManager, managers::TextureManager& textureManager, managers::WindowManager& windowManager)
    : m_shaderManager(shaderManager)
    , m_textureManager(textureManager)
    , m_windowManager(windowManager)
    , m_stack(shaderManager, textureManager)
{
    m_camera.SetViewport(0, 0, 640, 480);
    m_windowManager.registerHandler(&m_camera);
    loadResources();
}

void Context::run()
{
    glm::mat4 p, v;
    m_camera.Update();
    m_camera.GetMatricies(p, v);

    Shader* s = m_shaderManager.getShader("BasicShader");
    s->setUniform("view", v);
    s->setUniform("camera", glm::vec4(m_camera.GetPosition(), 1));

    m_stack.draw();
}

void Context::loadResources()
{
    m_shaderManager.loadShader("BasicShader", "resources/shaders/basic.vs", "resources/shaders/basic.fs");

    Shader* s = m_shaderManager.getShader("BasicShader");
    s->bind();
    s->enableAttribArray("position");
    s->enableAttribArray("color");
    s->enableAttribArray("uv");
    s->enableAttribArray("normal");
    glEnableVertexAttribArray(4);
    glEnableVertexAttribArray(5);
    glEnableVertexAttribArray(6);
    glEnableVertexAttribArray(7);

    glm::mat4 p, v;
    m_camera.Update();
    m_camera.GetMatricies(p, v);
    s->setUniform("projection", p);

    m_textureManager.load("smile", "resources/images/smile.tif");
    m_textureManager.load("smile2", "resources/images/smile2.tif");

//START TEST CODE
    auto m = new drawable::Model("resources/models/cube.obj", m_shaderManager.getShader("BasicShader"));
    m->setTransform(glm::translate(glm::mat4(1.f), glm::vec3(-1.1f,0,-5.f)));
    m_stack.submit(m);

    auto m2 = new drawable::Model("resources/models/teapot.obj", m_shaderManager.getShader("BasicShader"));
    m2->setTransform(glm::translate(glm::mat4(1.f), glm::vec3(-3.1f,0,-10.f)));
    m_stack.submit(m2);

    for(int i =0 ; i<10; i++)
    {
        auto m3 = new drawable::Model("resources/models/monkey.obj", m_shaderManager.getShader("BasicShader"));
        m3->setTransform(glm::translate(glm::mat4(1.f), glm::vec3(-5.f,-5 + 2*i,-5.f)));
        m_stack.submit(m3);
    }

    drawable::BatchRenderer* batch = new drawable::BatchRenderer(m_shaderManager.getShader("BasicShader"), glm::translate(glm::mat4(1.f), glm::vec3(-1,0,0)));
    batch->setTransform(glm::translate(glm::mat4(1.f), glm::vec3(1,0,0)));

    for(float x=-1; x<=1.f; x+=.0625f/2.f)
    {
        for(float y=-1; y<=1.f; y+=.0625f/2.f)
        {
            batch->submit(new drawable::Triangle( glm::vec3(x,y, -1), m_shaderManager.getShader("BasicShader") ));
        }
    }
    m_stack.submit(batch);

    auto shader = m_shaderManager.getShader("BasicShader");
    drawable::Rectangle* r = new drawable::Rectangle(glm::vec3(0,0,0), shader);
    r->setTexture(m_textureManager.find("smile"));
    r->setTransform(glm::translate(glm::mat4(1.f), glm::vec3(-.5f,0,0)));
    m_stack.submit(r);

    drawable::Rectangle* r2 = new drawable::Rectangle(glm::vec3(0,0,0), shader);
    r2->setTexture(m_textureManager.find("smile2"));
    r2->setTransform(glm::translate(glm::mat4(1.f), glm::vec3(.5f,0,0)));
    m_stack.submit(r2);
//END TEST CODE
}
