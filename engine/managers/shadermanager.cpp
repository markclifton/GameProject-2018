#include "shadermanager.h"

namespace managers
{
    shaderPair::shaderPair(std::unique_ptr<Shader> shader, std::string name)
        : shader( std::move(shader))
        , name(name)
    {}

    ShaderManager::ShaderManager()
    {
    }

    bool ShaderManager::loadShader(const std::string& name, const std::string& vsPath, const std::string& fsPath)
    {
        if( getShader( name ) == nullptr )
        {
            m_shaders.emplace_back(std::make_unique<Shader>(vsPath, fsPath), name);
            return true;
        }
        return false;
    }

    Shader* ShaderManager::getShader(const std::string& name)
    {
        for( auto& shader: m_shaders )
        {
            if(shader.name.compare(name) == 0)
            {
                return shader.shader.get();
            }
        }
        return nullptr;
    }

    void ShaderManager::reset()
    {
        m_shaders.clear();
    }
}
