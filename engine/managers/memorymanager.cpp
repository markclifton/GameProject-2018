#include "memorymanager.h"

namespace ps
{
namespace managers
{
MemoryManager& MemoryManager::Get()
{
    static MemoryManager manager;
    return manager;
}

MemoryManager::~MemoryManager()
{
    for(auto& block : allocatedMemoryMap_)
    {
        delete [] block.second;
    }
    allocatedMemoryMap_.clear();
}

MemoryBlock MemoryManager::AllocateMemory(const MemoryHandle& handle, const unsigned long& bytes)
{
    ReleaseMemory(handle);
    std::lock_guard<std::mutex> lock(mutex_);
    allocatedMemoryMap_[handle] = new unsigned char[bytes];
    return allocatedMemoryMap_[handle];
}

MemoryBlock MemoryManager::GetMemory(const MemoryHandle& handle)
{
    std::lock_guard<std::mutex> lock(mutex_);
    return allocatedMemoryMap_.count(handle) > 0 ? allocatedMemoryMap_[handle] : nullptr;;
}

void MemoryManager::ReleaseMemory(const MemoryHandle& handle)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if(allocatedMemoryMap_.count(handle))
    {
        delete [] allocatedMemoryMap_[handle];
        allocatedMemoryMap_.erase(handle);
    }
}
}
}
