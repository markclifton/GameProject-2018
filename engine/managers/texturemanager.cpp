#include "texturemanager.h"

#include <iostream>

namespace managers
{
    TextureManager::TextureManager()
    {
    }

    TextureManager::~TextureManager()
    {
        reset();
    }

    void TextureManager::load(const std::string& name, const char* filename, GLenum image_format, GLint internal_format, GLint level, GLint border)
    {
        if(find(name) == nullptr)
        {
            m_textures.push_back(std::make_pair(name, std::make_unique<Texture>(filename, image_format, internal_format, level, border)));
        }
    }

    bool TextureManager::bind(const std::string& name, uint position)
    {
        Texture* texture = find(name);
        if( texture )
        {
            texture->bind(position);
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
                m_textures[i] = std::move(m_textures.back());
                m_textures.pop_back();
                return true;
            }
        }
        return false;
    }

    Texture* TextureManager::find(const std::string& name)
    {
        for(auto& texture : m_textures)
        {
            if(texture.first.compare(name) == 0)
            {
                return texture.second.get();
            }
        }
        return nullptr;
    }
}
