#include "context.h"

#include <glm/gtc/matrix_transform.hpp>

#include "drawable/triangle.h"
#include "drawable/model.h"
#include "drawable/rectangle.h"
#include "drawable/renderers/batch.h"

//TEST
#include "drawable/renderers/instanced.h"

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
    std::cout << "Loading Resources!\n" << std::endl;

    m_shaderManager.loadShader("BasicShader", "resources/shaders/basic.vs", "resources/shaders/basic.fs");
    Shader* s = m_shaderManager.getShader("BasicShader");
    s->bind();

    glm::mat4 p, v;
    m_camera.Update();
    m_camera.GetMatricies(p, v);
    s->setUniform("projection", p);

    m_textureManager.load("smile", "resources/images/smile.tif");
    m_textureManager.load("smile2", "resources/images/smile2.tif");
    m_textureManager.load("dirt", "resources/images/dirt.tif");

//START TEST CODE
    //Light Representation
    auto m = new drawable::Model("resources/models/cube.obj", s);
    m->setTransform(glm::translate(glm::mat4(1.f), glm::vec3(-1.5f,0,-5.5f)));
    m_stack.submit(m);

    auto m4 = new drawable::Model("resources/models/cube.obj", s);
    m4->setTransform(glm::translate(glm::mat4(1.f), glm::vec3(1.f,-.5f,-10.5f)));
    m4->setColor(glm::vec4(1,0,1,1));
    m_stack.submit(m4);

    //Model 1
    auto m2 = new drawable::Model("resources/models/teapot.obj", s);
    m2->setTransform(glm::translate(glm::mat4(1.f), glm::vec3(-3.1f,-1,-10.f)));
    m2->calculateNormals();
    m_stack.submit(m2);

    // Model 2
    auto m3 = new drawable::Model("resources/models/monkey.obj", s);
    m3->setTransform(glm::translate(glm::mat4(1.f), glm::vec3(-5.f,1,-5.f)));
    m_stack.submit(m3);

    // Floor
    auto instanced = new drawable::renderer::Instanced(s);

    //m_textureManager.load("cobble", "resources/images/BrickRound0105_5_SPEC.png");
    //auto cobble = new drawable::Model("resources/models/cobble.obj", s);
    //auto bbox = cobble->calculateBBox();
    //float width = bbox.max.x - bbox.min.x;
    //float depth = bbox.max.z - bbox.min.z;
    //cobble->setTexture(m_textureManager.find("cobble"));
    //cobble->calculateNormals();
    //instanced->submit(cobble);
    //instanced->setDrawType(GL_TRIANGLE_FAN);
    //for(int x=-4; x<4; x++)
    //{
    //    for(int z=-4; z<4; z++)
    //    {
    //        instanced->submit(glm::translate(glm::mat4(1.f), glm::vec3(x, -2, z-8)) * glm::scale(glm::mat4(1.f), glm::vec3(1/width, 1, 1/depth)));
    //    }
    //}

    auto cube = new drawable::Model("resources/models/cube2.obj", s);
    auto bbox = cube->calculateBBox();
    float width = bbox.max.x - bbox.min.x;
    float depth = bbox.max.z - bbox.min.z;
    cube->calculateNormals();
    cube->setTexture(m_textureManager.find("dirt"));
    instanced->submit(cube);
    for(int x=-10; x<10; x++)
    {
        for(int z=-10; z<10; z++)
        {
            instanced->submit(glm::translate(glm::mat4(1.f), glm::vec3(x, -2, z-8)) * glm::scale(glm::mat4(1.f), glm::vec3(1/width, 1, 1/depth)));
        }
    }

    m_stack.submit(instanced);

    //Triangle Wall
    drawable::renderer::Batch* batch = new drawable::renderer::Batch(s, glm::translate(glm::mat4(1.f), glm::vec3(-1,0,0)));
    batch->setTransform(glm::translate(glm::mat4(1.f), glm::vec3(1,0,0)));
    for(float x=-1; x<=1.f; x+=.0625f/2.f)
    {
        for(float y=-1; y<=1.f; y+=.0625f/2.f)
        {
            batch->submit(new drawable::Triangle( glm::vec3(x,y, -1), s ));
        }
    }
    m_stack.submit(batch);

    // Textured Faces
    drawable::Rectangle* r = new drawable::Rectangle(glm::vec3(0,0,0), s);
    r->setTexture(m_textureManager.find("smile"));
    r->setTransform(glm::translate(glm::mat4(1.f), glm::vec3(-.5f,0,0)));
    m_stack.submit(r);

    drawable::Rectangle* r2 = new drawable::Rectangle(glm::vec3(0,0,0), s);
    r2->setTexture(m_textureManager.find("smile2"));
    r2->setTransform(glm::translate(glm::mat4(1.f), glm::vec3(.5f,0,0)));
    m_stack.submit(r2);
//END TEST CODE
}
