#pragma once

namespace ps
{
class ContextBase
{
public:
    ContextBase();
    virtual ~ContextBase() = default;
    virtual void run() = 0;
    virtual void loadResources() = 0;
};
}
