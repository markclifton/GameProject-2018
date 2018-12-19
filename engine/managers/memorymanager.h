#pragma once

#include <map>
#include <mutex>

namespace ps
{
typedef unsigned long MemoryHandle;
typedef unsigned char* MemoryBlock;

namespace managers
{
class MemoryManager
{
public:
    static MemoryManager& Get();
    ~MemoryManager();
    MemoryBlock AllocateMemory(const MemoryHandle& handle, const unsigned long& bytes);
    MemoryBlock GetMemory(const MemoryHandle& handle);
    void ReleaseMemory(const MemoryHandle& handle);

private:
    std::mutex mutex_;
    std::map<MemoryHandle, MemoryBlock> allocatedMemoryMap_;
};
}
}
