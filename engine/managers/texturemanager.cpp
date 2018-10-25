#include "texturemanager.h"

#include <iostream>

namespace managers
{
    TextureManager::TextureManager()
    {
        for(int i=0; i<16; i++)
        {

        }
    }

    TextureManager::~TextureManager()
    {
        reset();
    }

    void TextureManager::load(const std::string& name, const char* filename, GLenum image_format, GLint internal_format, GLint level, GLint border)
    {
        if(find(name).lock())
        {
            //Already loaded texture
            return;
        }

        m_textures.push_back(std::make_pair(name, std::make_shared<Texture>(filename, image_format, internal_format, level, border)));
    }

    bool TextureManager::bind(const std::string& name, uint position)
    {
        auto wpTexture = find(name);
        if( auto spTexture = wpTexture.lock() )
        {
            spTexture->bind(position);
            return true;
        }
        return false;
    }

    void TextureManager::reset()
    {
        for(auto& texture : m_textures)
        {
            unload(texture.first);
        }
        m_textures.clear();
    }

    bool TextureManager::unload(const std::string& name)
    {
        for(size_t i=0; i<m_textures.size(); i++)
        {
            if(m_textures[i].first.compare(name) == 0)
            {
                m_textures[i] = m_textures.back();
                m_textures.pop_back();
                return true;
            }
        }
        return false;
    }

    std::weak_ptr<Texture> TextureManager::find(const std::string& name)
    {
        for(auto& texture : m_textures)
        {
            if(texture.first.compare(name) == 0)
            {
                return texture.second;
            }
        }
        return std::weak_ptr<Texture>();
    }
}
