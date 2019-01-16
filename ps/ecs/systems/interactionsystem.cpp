#include "interactionsystem.h"

#include "ps/ecs/ecsmanager.h"
#include "ps/ecs/entities/drawableentity.h"

#include "ps/ecs/components/inputcomponent.h"
#include "ps/ecs/components/movementcomponent.h"
#include "ps/ecs/components/interactioncomponent.h"

namespace ps
{
namespace ecs
{
InteractionSystem::InteractionSystem()
{
    components_.push_back(VertexComponent::Type);
    components_.push_back(MovementComponent::Type);
    components_.push_back(InteractionComponent::Type);
}

void InteractionSystem::update(std::vector<COMP_TYPE>, float, void** component)
{
    auto baseComponent = reinterpret_cast<BaseComponent*>(*component);
    auto thisEntity = reinterpret_cast<drawable::DrawableEntity*>(baseComponent->entityHandle);

    for(auto& entityRaw : ECSManager::get().entities_)
    {
        if(entityRaw.get() != thisEntity && entityRaw->NumComponentsForType(InputComponent::Type) > 0)
        {
            auto entity = reinterpret_cast<drawable::DrawableEntity*>(entityRaw.get());

            auto thisPosition = thisEntity->getTransform() * glm::vec4(thisEntity->verts()[0].pos,1);
            auto entityPosition = entity->getTransform() * glm::vec4(entity->verts()[0].pos,1);

            auto resultVector = entityPosition - thisPosition;
            resultVector = glm::normalize(resultVector);

            auto movement = reinterpret_cast<MovementComponent*>(thisEntity->GetComponentByTypeAndIndex(MovementComponent::Type, 0));
            movement->speed = resultVector * .001f;

            return;
        }
    }
}
}
}
