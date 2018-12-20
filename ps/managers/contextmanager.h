#pragma once

#include <map>
#include <string>

#include "ps/contexts/context.h"
#include "ps/managers/shadermanager.h"

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
    ContextManager(ContextManager const&) = delete;
    void operator=(ContextManager const&) = delete;

    std::vector<std::pair<std::string, std::unique_ptr<ContextBase>>> m_contexts;
    ContextBase* m_activeContext {nullptr};

};
}
}
