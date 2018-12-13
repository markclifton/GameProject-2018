#include "shadowentity.h"

namespace ecs
{

ShadowEntity::ShadowEntity(Shader* shader, Texture* texture)
{
    cameraComponent.camera = new Camera3D();
    cameraComponent.camera->SetViewport(0, 0, 1024, 1024);
    cameraComponent.camera->Update(true);
    cameraComponent.camera->setPosition(glm::vec3(1.5, 10, 5.5));
    cameraComponent.camera->setPitch(glm::radians(-89.f));

    ShaderComponent shaderComponent;
    shaderComponent.shader = shader;

    TextureComponent textureComponent;
    textureComponent.texture = texture;

    AddComponentOfType(CameraComponent::Type, CameraComponent::CreationFN(this, &cameraComponent));
    AddComponentOfType(ShaderComponent::Type, ShaderComponent::CreationFN(this, &shaderComponent));
    AddComponentOfType(TextureComponent::Type, TextureComponent::CreationFN(this, &textureComponent));
}

}
