#pragma once

#include <memory>
#include <vector>

#include "../shaders/shader.h"

namespace managers
{
    struct shaderPair
    {
        shaderPair(std::unique_ptr<Shader> shader, std::string name);
        std::unique_ptr<Shader> shader {nullptr};
        std::string name;
    };

    class ShaderManager
    {
    public:
        ShaderManager();

        bool loadShader(const std::string& name, const std::string& vsPath, const std::string& fsPath);
        Shader* getShader(const std::string& name);

    private:
        std::vector<shaderPair> m_shaders; //Vector for efficiency
    };
}
