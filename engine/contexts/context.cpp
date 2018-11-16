#include "context.h"

#include <glm/gtc/matrix_transform.hpp>

#include "drawable/triangle.h"
#include "drawable/model.h"
#include "drawable/rectangle.h"
#include "drawable/renderers/batch.h"

#include "drawable/renderers/instanced.h"

Context::Context(managers::SoundManager& soundManager, managers::ShaderManager& shaderManager, managers::TextureManager& textureManager, managers::WindowManager& windowManager)
    : m_soundManager(soundManager)
    , m_shaderManager(shaderManager)
    , m_textureManager(textureManager)
    , m_windowManager(windowManager)
    , m_stack(shaderManager, textureManager)
{
    m_camera.SetViewport(0, 0, 1280, 720);
    m_shadowCamera.SetViewport(0, 0, 1024, 1024);
    m_windowManager.registerHandler(&m_camera);
    loadResources();
}

void Context::run()
{
    // Shadow Pass
    glm::mat4 pS, vS;
    m_shadowCamera.Update();
    m_shadowCamera.GetMatricies(pS, vS);
    pS = glm::ortho<float>(-10, 10, -10, 10, 1, 100);
    {
        m_shadowTexture->setAsRenderTarget();

        Shader* s = m_shaderManager.getShader("Shadow");
        s->bind();
        s->setUniform("projection", pS);
        s->setUniform("view", vS);
        m_stack.draw();

        m_windowManager.setAsRenderTarget();
    }

    // Regular Pass
    {
        glm::mat4 p, v;
        m_camera.Update();
        m_camera.GetMatricies(p, v);

        m_shadowTexture->bind(0);

        Shader* s = m_shaderManager.getShader("BasicShader");
        s->bind();
        s->setUniform("projection", p);
        s->setUniform("view", v);
        s->setUniform("camera", glm::vec4(m_camera.GetPosition(), 1));

        glm::mat4 biasMatrix(
                    0.5, 0.0, 0.0, 0.0,
                    0.0, 0.5, 0.0, 0.0,
                    0.0, 0.0, 0.5, 0.0,
                    0.5, 0.5, 0.5, 1.0
                    );
        glm::mat4 depthBiasMVP = biasMatrix*pS*vS;
        s->setUniform("shadow", depthBiasMVP);

        lights::setLights(m_pointlights, s, v);
        lights::setLights(m_spotlights, s, v);

        m_stack.draw();
    }
}

void Context::loadResources()
{
    std::cout << "Loading Resources!\n" << std::endl;

    m_shaderManager.loadShader("FBO", "resources/shaders/fbo.vs", "resources/shaders/fbo.fs");
    m_shaderManager.loadShader("Shadow", "resources/shaders/shadow.vs", "resources/shaders/shadow.fs");

    m_shaderManager.loadShader("BasicShader", "resources/shaders/basic.vs", "resources/shaders/basic.fs");
    Shader* s = m_shaderManager.getShader("BasicShader");
    s->bind();

    m_shadowCamera.Update(true);
    m_shadowCamera.setPosition(glm::vec3(1.5, 10, 5.5));
    m_shadowCamera.setPitch(glm::radians(-89.f));

    m_textureManager.load("smile", "resources/images/smile.tif");
    m_textureManager.load("smile2", "resources/images/smile2.tif");
    m_textureManager.load("dirt", "resources/images/dirt.tif");

    m_textureManager.submitTexture(std::make_unique<Texture>("Shadows", 1024, 1024));
    m_shadowTexture = m_textureManager.find("Shadows");

    m_soundManager.loadSound("rain", "resources/sounds/rain.mp3");

    //START TEST CODE
    //Light Representation
    {
        auto m = new drawable::Model("resources/models/cube.obj", s);
        m->setTransform(glm::translate(glm::mat4(1.f), glm::vec3(-1.5f,10,-5.5f)));
        m_stack.submit(m);

        lights::PointLight plight;
        plight.color = glm::vec3(1,1,1);
        plight.elc = glm::vec3(1,0,0);
        plight.intensity = 10000;
        plight.pos_w = glm::vec3(-1,10,-5);
        m_pointlights.push_back(plight);

        auto m4 = new drawable::Model("resources/models/cube.obj", s);
        m4->setTransform(glm::translate(glm::mat4(1.f), glm::vec3(1.f,-.5f,-10.5f)));
        m4->setColor(glm::vec4(1,0,1,1));
        m_stack.submit(m4);

        lights::SpotLight slight;
        slight.color = glm::vec3(1,0,1);
        slight.elc = glm::vec3(1,0,0);
        slight.intensity = 25;
        slight.pos_w = glm::vec3(1, 0, -10);
        slight.cutoff = .5f;
        slight.direction = glm::vec3(-1,0,0);
        m_spotlights.push_back(slight);
    }

    //Model 1 - teapot
    {
        auto m2 = new drawable::Model("resources/models/teapot.obj", s);
        m2->setTransform(glm::translate(glm::mat4(1.f), glm::vec3(-3.1f,-1,-10.f)));
        m2->calculateNormals();
        m_stack.submit(m2);
    }

    // Model 2 - suzanne
    {
        auto m3 = new drawable::Model("resources/models/monkey.obj", s);
        m3->setTransform(glm::translate(glm::mat4(1.f), glm::vec3(-5.f,1,-5.f)));
        m_stack.submit(m3);
    }

    // Floor
    {
        auto instanced = new drawable::renderer::Instanced(s);

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
    }

    //Triangle Wall
    {
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
    }

    // Textured Faces
    {
        drawable::Rectangle* r = new drawable::Rectangle(glm::vec3(0,0,0), s);
        r->setTexture(m_textureManager.find("smile"));
        r->setTransform(glm::translate(glm::mat4(1.f), glm::vec3(-.5f,0,0)));
        m_stack.submit(r);

        drawable::Rectangle* r2 = new drawable::Rectangle(glm::vec3(0,0,0), s);
        r2->setTexture(m_textureManager.find("Shadows"));
        r2->setTransform(glm::translate(glm::mat4(1.f), glm::vec3(1.5f,0,0)));
        m_stack.submit(r2);
    }
    //END TEST CODE

    std::cout << "Finished Loading Resources!\n" << std::endl;
}
