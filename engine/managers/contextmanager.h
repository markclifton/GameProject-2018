#pragma once

#include <map>
#include <string>

#include "contexts/context.h"
#include "shadermanager.h"

namespace ps
{
namespace managers
{
class ContextManager
{
public:
    ContextManager();
    ~ContextManager();

    ContextBase* find(const std::string& name);
    bool setContext(const std::string& name);
    bool addContext(const std::string& name , std::unique_ptr<ContextBase> context);
    bool removeContext(const std::string& name);

    void run();

    void reset();

private:
    std::vector<std::pair<std::string, std::unique_ptr<ContextBase>>> m_contexts;
    ContextBase* m_activeContext {nullptr};

};
}
}
