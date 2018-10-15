#include "shadermanager.h"

namespace managers
{
    ShaderManager::ShaderManager()
    {
    }

    bool ShaderManager::loadShader(const std::string& name, const std::string& vsPath, const std::string& fsPath)
    {
        if( getShader( name ) == nullptr )
        {
            m_shaders.emplace_back(name, std::make_unique<Shader>(vsPath, fsPath));
            return true;
        }
        return false;
    }

    Shader* ShaderManager::getShader(const std::string& name)
    {
        for( auto& shader: m_shaders )
        {
            if(shader.first.compare(name) == 0)
            {
                return shader.second.get();
            }
        }
        return nullptr;
    }

    void ShaderManager::reset()
    {
        m_shaders.clear();
    }
}
