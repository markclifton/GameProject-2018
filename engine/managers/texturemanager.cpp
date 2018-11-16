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
        m_textures.push_back(std::make_unique<Texture>(name, filename, image_format, internal_format, level, border));
    }
}

Texture* TextureManager::find(const std::string& name)
{
    for(auto& texture : m_textures)
    {
        if(texture->name().compare(name) == 0)
        {
            return texture.get();
        }
    }
    return nullptr;
}

bool TextureManager::bind(const std::string& name, uint32_t position)
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
    m_textures.clear();
}

void TextureManager::submitTexture(std::unique_ptr<Texture> texture)
{
    if(texture == nullptr)
    {
        return;
    }

    if(find(texture->name()) == nullptr)
    {
        m_textures.push_back(std::move(texture));
    }
}

bool TextureManager::unload(const std::string& name)
{
    for(size_t i=0; i<m_textures.size(); i++)
    {
        if(m_textures[i]->name().compare(name) == 0)
        {
            if(i != m_textures.size() - 1)
            {
                m_textures[i] = std::move(m_textures.back());
            }
            m_textures.pop_back();
            return true;
        }
    }
    return false;
}
}
