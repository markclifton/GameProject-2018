#pragma once

#include "../renderer/batchrenderer.h"

class Context
{
public:
    Context();

    void run();

private:
    BatchRenderer m_batch;
};
