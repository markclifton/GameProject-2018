#pragma once

#include <functional>
#include <tuple>
#include <vector>

#include "ps/managers/memorymanager.h"

namespace ps
{
namespace ecs
{
class BaseComponent;

typedef void* ENTITY_HANDLE;

typedef unsigned long COMP_TYPE;
typedef std::function<void*(ENTITY_HANDLE, BaseComponent*)> COMP_CTOR;
typedef std::function<void(BaseComponent*)> COMP_DTOR;
typedef unsigned long COMP_SIZE;
typedef std::tuple<COMP_TYPE, COMP_SIZE, COMP_CTOR, COMP_DTOR> RAWCOMP;

template <typename Component>
void* CreateComp(ENTITY_HANDLE handle, BaseComponent* component)
{
    Component* newComponent = new(Component::componentZero + Component::componentTotalOffset) Component(*reinterpret_cast<Component*>(component));
    Component::componentTotalOffset += Component::Size;
    newComponent->entityHandle = handle;
    return newComponent;
}

template <typename Component>
void ReleaseComp(BaseComponent*)
{
    //TODO
    //Shift last component to this component's offset
    //Call dtor on this component
}

class BaseComponent
{
public:
    static COMP_TYPE RegisterComponent(COMP_SIZE size, COMP_CTOR ctor, COMP_DTOR dtor);
    static bool ValidComponent(COMP_TYPE type);
    static RAWCOMP* GetRaw(COMP_TYPE type);
    static const std::vector<RAWCOMP>& GetAllComponents();

    ENTITY_HANDLE entityHandle {nullptr};
private:
    static std::vector<RAWCOMP> availableComponents_;
    static std::mutex registerMutex_;
    static COMP_TYPE nextType_;
};

template <typename Component>
class IComponent : public BaseComponent
{
public:
    static const COMP_TYPE Type;
    static const COMP_SIZE Size;
    static const COMP_CTOR CreationFN;
    static const COMP_DTOR ReleaseFN;

    static MemoryBlock componentZero;
    static unsigned long componentTotalOffset;
};

template <typename Component>
const COMP_TYPE IComponent<Component>::Type(RegisterComponent(sizeof(Component), CreateComp<Component>, ReleaseComp<Component>));

template <typename Component>
const COMP_SIZE IComponent<Component>::Size(sizeof(Component));

template <typename Component>
const COMP_CTOR IComponent<Component>::CreationFN(CreateComp<Component>);

template <typename Component>
const COMP_DTOR IComponent<Component>::ReleaseFN(ReleaseComp<Component>);

template <typename Component>
MemoryBlock IComponent<Component>::componentZero(MemoryManager::Get().AllocateMemory(Type, static_cast<unsigned long>(1e8)));

template <typename Component>
unsigned long IComponent<Component>::componentTotalOffset(0);
}
}
