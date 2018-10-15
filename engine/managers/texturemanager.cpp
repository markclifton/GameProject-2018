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

    bool TextureManager::load(const std::string& name, const char* filename, GLenum image_format, GLint internal_format, GLint level, GLint border)
    {
        if(find(name) != 0)
        {
            std::cerr << "Texture: " << name << " already loaded\n";
            return false;
        }

        FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(filename, 0);
        if(fif == FIF_UNKNOWN)
            fif = FreeImage_GetFIFFromFilename(filename);
        if(fif == FIF_UNKNOWN)
            return false;

        //check that the plugin has reading capabilities and load the file
        FIBITMAP *dib = nullptr;
        if(FreeImage_FIFSupportsReading(fif))
        {
            dib = FreeImage_Load(fif, filename);
        }

        if(!dib)
        {
            return false;
        }

        //retrieve the image data
        BYTE*  bits = FreeImage_GetBits(dib);
        unsigned int width = FreeImage_GetWidth(dib);
        unsigned int height = FreeImage_GetHeight(dib);
        if((bits == nullptr) || (width == 0) || (height == 0))
        {
            return false;
        }


        GLuint gl_texID = 0;
        glGenTextures(1, &gl_texID);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gl_texID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, level, internal_format, static_cast<int>(width), static_cast<int>(height), border, image_format, GL_UNSIGNED_BYTE, bits);

        FreeImage_Unload(dib);
        return true;
    }

    bool TextureManager::bind(const std::string& name)
    {
        auto id = find(name);
        if( id != 0)
        {
            glBindTexture(GL_TEXTURE_2D, id);
            return true;
        }
        return false;
    }

    bool TextureManager::unload(const std::string& name)
    {
        for(size_t i=0; i<m_textures.size(); i++)
        {
            if(m_textures[i].first.compare(name) == 0)
            {
                glDeleteTextures(1, &m_textures[i].second);
                m_textures[i] = m_textures.back();
                m_textures.pop_back();
                return true;
            }
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

    GLuint TextureManager::find(const std::string& name)
    {
        for(auto& texture : m_textures)
        {
            if(texture.first.compare(name) == 0)
            {
                return texture.second;
            }
        }
        return 0;
    }
}
