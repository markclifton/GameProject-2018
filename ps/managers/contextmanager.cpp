#include "contextmanager.h"

#include <memory>

namespace ps
{
namespace managers
{
ContextManager::ContextManager()
{
}

ContextManager::~ContextManager()
{
}

ContextBase* ContextManager::find(const std::string& name)
{
    for(auto& contextpair : m_contexts)
    {
        if(contextpair.first.compare(name) == 0)
        {
            return contextpair.second.get();
        }
    }
    return nullptr;
}

bool ContextManager::setContext(const std::string& name)
{
    auto context = find(name);
    if(context != nullptr)
    {
        m_activeContext = context;
        return true;
    }
    return false;
}

bool ContextManager::addContext(const std::string& name, std::unique_ptr<ContextBase> state)
{
    auto context = find(name);
    if(context == nullptr)
    {
        m_contexts.emplace_back(name, std::move(state));
        return true;
    }
    return false;
}

bool ContextManager::removeContext(const std::string& name)
{
    for(size_t i=0; i<m_contexts.size(); i++)
    {
        if(m_contexts[i].first.compare(name) == 0)
        {
            if(m_contexts[i].second.get() == m_activeContext) //TODO: Not thread-safe
            {
                return false;
            }

            m_contexts[i].first = m_contexts.back().first;
            m_contexts[i].second = std::move(m_contexts.back().second);
            m_contexts.pop_back();
            return true;
        }
    }
    return false;
}

void ContextManager::run()
{
    if(m_activeContext != nullptr)
    {
        m_activeContext->run();
    }
}

void ContextManager::reset()
{
    m_activeContext = nullptr;
    m_contexts.clear();
}
}
}
