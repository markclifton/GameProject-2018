#include "context.h"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

#include "drawable/model.h"
#include "drawable/rectangle.h"
#include "drawable/renderers/batch.h"
#include "drawable/triangle.h"

#include "drawable/renderers/instanced.h"

#include "ecs/components/cameracomponent.h"
#include "ecs/components/shadercomponent.h"
#include "ecs/components/texturecomponent.h"

Context::Context(managers::SoundManager& soundManager, managers::ShaderManager& shaderManager, managers::TextureManager& textureManager, managers::WindowManager& windowManager)
    : soundManager_(soundManager)
    , shaderManager_(shaderManager)
    , textureManager_(textureManager)
    , windowManager_(windowManager)
    , stack_(shaderManager, textureManager)
{
    m_camera.SetViewport(0, 0, 1280, 720);
    shadowCamera_.SetViewport(0, 0, 1024, 1024);
    windowManager_.registerHandler(&m_camera);
    loadResources();
}

void Context::run()
{
    // Shadow Pass
    ecs::ECSManager::get().updateSystems({CameraComponent::Type, ShaderComponent::Type, TextureComponent::Type});

    glm::mat4 pS, vS;
    shadowEntity_->cameraComponent.camera->GetMatricies(pS, vS);
    pS = glm::ortho<float>(-10, 10, -10, 10, 1, 100);

    // Regular Pass
    {
        windowManager_.setAsRenderTarget();

        glm::mat4 p, v;
        m_camera.Update();
        m_camera.GetMatricies(p, v);

        textureManager_.find("Shadows")->bind(0);

        Shader* s = shaderManager_.getShader("BasicShader");
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

        lights::setLights(pointlights_, s, v);
        lights::setLights(spotlights_, s, v);

        stack_.draw();
        ecs::ECSManager::get().updateSystems({VertexComponent::Type, ShaderComponent::Type});
    }
}

void Context::loadResources()
{
    //START TEST CODE (FIX MEMORY LEAKS...)
    //Light Representation
    std::cout << "Loading Resources!\n" << std::endl;
    ecs::ECSManager::get().addSystem(1, &renderingSystem_); //TODO: Rethink this...
    ecs::ECSManager::get().addSystem(2, &shadowSystem_); //TODO: Rethink this...

    shaderManager_.loadShader("FBO", "resources/shaders/fbo.vs", "resources/shaders/fbo.fs");
    shaderManager_.loadShader("Shadow", "resources/shaders/shadow.vs", "resources/shaders/shadow.fs");

    shaderManager_.loadShader("BasicShader", "resources/shaders/basic.vs", "resources/shaders/basic.fs");
    Shader* s = shaderManager_.getShader("BasicShader");
    s->bind();

    textureManager_.load("smile", "resources/images/smile.tif");
    textureManager_.load("smile2", "resources/images/smile2.tif");
    textureManager_.load("dirt", "resources/images/dirt.tif");

    textureManager_.submitTexture(std::make_unique<Texture>("Shadows", 1024, 1024));
    shadowEntity_ = new ecs::ShadowEntity(shaderManager_.getShader("Shadow"), textureManager_.find("Shadows"));
    ecs::ECSManager::get().addEntity(shadowEntity_);

    soundManager_.loadSound("rain", "resources/sounds/rain.mp3");

    {
        auto m = new drawable::Model("resources/models/cube.obj", s);
        m->setTransform(glm::translate(glm::mat4(1.f), glm::vec3(-1.5f,10,-5.5f)));
        ecs::ECSManager::get().addEntity(m);

        lights::PointLight plight;
        plight.color = glm::vec3(1,1,1);
        plight.elc = glm::vec3(1,0,0);
        plight.intensity = 10000;
        plight.pos_w = glm::vec3(-1,10,-5);
        pointlights_.push_back(plight);

        auto m4 = new drawable::Model("resources/models/cube.obj", s);
        m4->setTransform(glm::translate(glm::mat4(1.f), glm::vec3(1.f,-.5f,-10.5f)));
        m4->setColor(glm::vec4(1,0,1,1));
        ecs::ECSManager::get().addEntity(m4);

        lights::SpotLight slight;
        slight.color = glm::vec3(1,0,1);
        slight.elc = glm::vec3(1,0,0);
        slight.intensity = 25;
        slight.pos_w = glm::vec3(1, 0, -10);
        slight.cutoff = .5f;
        slight.direction = glm::vec3(-1,0,0);
        spotlights_.push_back(slight);
    }

    //Model 1 - teapot
    {
        auto m2 = new drawable::Model("resources/models/teapot.obj", s);
        m2->setTransform(glm::translate(glm::mat4(1.f), glm::vec3(-3.1f,-1,-10.f)));
        m2->calculateNormals();
        ecs::ECSManager::get().addEntity(m2);
    }

    // Model 2 - suzanne
    {
        auto m3 = new drawable::Model("resources/models/monkey.obj", s);
        m3->setTransform(glm::translate(glm::mat4(1.f), glm::vec3(-5.f,1,-5.f)));
        ecs::ECSManager::get().addEntity(m3);
    }

    // Floor
    {
        auto instanced = new drawable::renderer::Instanced(s);

        auto cube = new drawable::Model("resources/models/cube2.obj", s);
        auto bbox = cube->calculateBBox();
        float width = bbox.max.x - bbox.min.x;
        float depth = bbox.max.z - bbox.min.z;
        cube->calculateNormals();
        cube->setTexture(textureManager_.find("dirt"));
        instanced->submit(cube);
        for(int x=-10; x<10; x++)
        {
            for(int z=-10; z<10; z++)
            {
                instanced->submit(glm::translate(glm::mat4(1.f), glm::vec3(x, -2, z-8)) * glm::scale(glm::mat4(1.f), glm::vec3(1/width, 1, 1/depth)));
            }
        }

        stack_.submit(instanced);
    }

    //Triangle Wall //TODO: FIXME Horrible performance with doing batch rendering
    //{
    //    drawable::renderer::Batch* batch = new drawable::renderer::Batch(s, glm::translate(glm::mat4(1.f), glm::vec3(-1,0,0)));
    //    batch->setTransform(glm::translate(glm::mat4(1.f), glm::vec3(1,0,0)));
    //    for(float x=-1; x<=1.f; x+=.0625f/2.f)
    //    {
    //        for(float y=-1; y<=1.f; y+=.0625f/2.f)
    //        {
    //            batch->submit(new drawable::Triangle( glm::vec3(x,y, -1), s ));
    //        }
    //    }
    //    m_stack.submit(batch);
    //}

    // Textured Faces
    {
        drawable::Rectangle* r = new drawable::Rectangle(glm::vec3(0,0,0), s);
        r->setTexture(textureManager_.find("smile"));
        r->setTransform(glm::translate(glm::mat4(1.f), glm::vec3(-.5f,0,0)));
        ecs::ECSManager::get().addEntity(r);

        drawable::Rectangle* r2 = new drawable::Rectangle(glm::vec3(0,0,0), s);
        r2->setTexture(textureManager_.find("smile2"));
        r2->setTransform(glm::translate(glm::mat4(1.f), glm::vec3(1.5f,0,0)));
        ecs::ECSManager::get().addEntity(r2);

        // Shadow Map
        drawable::Rectangle* r3 = new drawable::Rectangle(glm::vec3(0,0,0), s);
        r3->setTexture(textureManager_.find("Shadows"));
        r3->setTransform(glm::translate(glm::mat4(1.f), glm::vec3(3.5f,0,0)));
        ecs::ECSManager::get().addEntity(r3);
    }
    //END TEST CODE

    std::cout << "Finished Loading Resources!\n" << std::endl;
    soundManager_.playSound("rain");
}
