#include "contextmanager.h"

#include <iostream>
#include <string>

#include "windowmanager.h"

ContextManager::ContextManager()
    : m_nextId(0)
{
}

ContextManager::~ContextManager()
{
    for(auto& state : m_contexts)
    {
        delete state.second;    
    }
}

bool ContextManager::setContext(const int& id)
{
    if(m_contexts.find(id) != m_contexts.end())
    {
        m_activeContext = m_contexts[id];
        return true;
    }
    return false;
}

bool ContextManager::addContext(int& id, Context* state)
{
    id = m_nextId++;
    m_contexts.insert(std::make_pair(id, state));
    return true;
}

bool ContextManager::removeContext(const int& id)
{
    auto state = m_contexts.find(id);
    if(state != m_contexts.end() && state->second != m_activeContext)
    {
        delete state->second;
        m_contexts.erase(state);
        return true;
    }
    return false;
}

void ContextManager::runContext()
{
    if(m_activeContext != nullptr)
    {
        m_activeContext->run();
    }
}
