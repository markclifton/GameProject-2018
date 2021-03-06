#pragma once

#include <memory>
#include <vector>

#include "ps/shaders/shader.h"

namespace ps
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
    ShaderManager(ShaderManager const&) = delete;
    void operator=(ShaderManager const&) = delete;

    std::vector<std::pair<std::string, std::unique_ptr<Shader>>> m_shaders; //Vector for efficiency
};
}
