#pragma once

#include <memory>
#include <vector>

#include "shaders/shader.h"

namespace ps
{
namespace managers
{
class ShaderManager
{
    ShaderManager();
public:
    static ShaderManager& Get()
    {
        static ShaderManager manager;
        return manager;
    }

    bool loadShader(const std::string& name, const std::string& vsPath, const std::string& fsPath);
    Shader* getShader(const std::string& name);

    void reset();

private:
    std::vector<std::pair<std::string, std::unique_ptr<Shader>>> m_shaders; //Vector for efficiency
};
}
}
