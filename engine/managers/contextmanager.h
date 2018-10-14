#pragma once

#include <map>
#include <string>

#include "../contexts/context.h"
#include "shadermanager.h"

namespace managers
{
    struct contextPair
    {
        contextPair(std::string name, std::unique_ptr<Context> context);

        std::string name;
        std::unique_ptr<Context> context;
    };

    class ContextManager
    {
    public:
        ContextManager();
        ~ContextManager();

        Context* find(const std::string& name);
        bool setContext(const std::string& name);
        bool addContext(const std::string& name , std::unique_ptr<Context> context);
        bool removeContext(const std::string& name);

        void runContext();

        void reset();

    private:
        std::vector<contextPair> m_contexts;
        Context* m_activeContext {nullptr};

    };
}
