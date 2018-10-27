#pragma once

#include <map>
#include <string>

#include "contexts/context.h"
#include "shadermanager.h"

namespace managers
{
    class ContextManager
    {
    public:
        ContextManager();
        ~ContextManager();

        Context* find(const std::string& name);
        bool setContext(const std::string& name);
        bool addContext(const std::string& name , std::unique_ptr<Context> context);
        bool removeContext(const std::string& name);

        void run();

        void reset();

    private:
        std::vector<std::pair<std::string, std::unique_ptr<Context>>> m_contexts;
        Context* m_activeContext {nullptr};

    };
}
