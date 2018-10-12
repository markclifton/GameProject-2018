#pragma once

#include <map>

#include "../contexts/context.h"

class ContextManager
{
public:
    ContextManager();
    ~ContextManager();
    
    bool setContext(const int& id);
    bool addContext(int& id, Context* context);
    bool removeContext(const int& id);

    void runContext();

private:
    int m_nextId; 
    std::map<int, Context*> m_contexts;

    Context* m_activeContext {nullptr};
};
