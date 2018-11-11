#include "texture.h"

#include <string.h>

Texture::Texture(const std::string& name, const std::string& filename, GLenum image_format, GLint internal_format, GLint level, GLint border)
    : m_name(name)
{
    FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(filename.c_str(), 0);
    if(fif == FIF_UNKNOWN)
        fif = FreeImage_GetFIFFromFilename(filename.c_str());
    if(fif == FIF_UNKNOWN)
    {
        return;
    }
    //check that the plugin has reading capabilities and load the file
    FIBITMAP *dib = nullptr;
    if(FreeImage_FIFSupportsReading(fif))
    {
        dib = FreeImage_Load(fif, filename.c_str());
    }

    if(!dib)
    {
        return;
    }

    //retrieve the image data
    BYTE*  bits = FreeImage_GetBits(dib);
    unsigned int width = FreeImage_GetWidth(dib);
    unsigned int height = FreeImage_GetHeight(dib);
    if((bits == nullptr) || (width == 0) || (height == 0))
    {
        return;
    }

    glGenTextures(1, &m_textureID);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, level, internal_format, static_cast<int>(width), static_cast<int>(height), border, image_format, GL_UNSIGNED_BYTE, bits);

    FreeImage_Unload(dib);

    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_textureID);
}

void Texture::bind(const uint32_t& index)
{
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
}
