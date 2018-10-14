#include "contextmanager.h"

#include <memory>

namespace managers
{
    contextPair::contextPair(std::string name, std::unique_ptr<Context> context)
        : name(name)
        , context( std::move(context) )
    {}

    ContextManager::ContextManager()
    {
    }

    ContextManager::~ContextManager()
    {
    }

    Context* ContextManager::find(const std::string& name)
    {
        for(auto& contextpair : m_contexts)
        {
            if(contextpair.name.compare(name) == 0)
            {
                return contextpair.context.get();
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

    bool ContextManager::addContext(const std::string& name, std::unique_ptr<Context> state)
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
            if(m_contexts[i].name.compare(name) == 0)
            {
                if(m_contexts[i].context.get() == m_activeContext) //TODO: Not thread-safe
                {
                    return false;
                }

                m_contexts[i].name = m_contexts.back().name;
                m_contexts[i].context = std::move(m_contexts.back().context);
                m_contexts.pop_back();
                return true;
            }
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
}
