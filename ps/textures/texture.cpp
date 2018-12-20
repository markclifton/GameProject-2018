#include "texture.h"

#include <string.h>

namespace ps
{
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
    m_width = static_cast<int>(FreeImage_GetWidth(dib));
    m_height = static_cast<int>(FreeImage_GetHeight(dib));
    if((bits == nullptr) || (m_width == 0) || (m_height == 0))
    {
        return;
    }

    glGenTextures(1, &m_textureID);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, level, internal_format, static_cast<int>(m_width), static_cast<int>(m_height), border, image_format, GL_UNSIGNED_BYTE, bits);

    FreeImage_Unload(dib);

    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(const std::string& name, int width, int height)
    : m_name(name)
    , m_width(width)
    , m_height(height)
{
    glGenFramebuffers(1, &m_fbo);
    setAsRenderTarget();

    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, width, height, 0,GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_textureID, 0);
}

Texture::~Texture()
{
}

void Texture::setAsRenderTarget()
{
    std::vector<GLenum> buffers { GL_NONE };
    setAsRenderTarget(buffers);
}

void Texture::setAsRenderTarget(const std::vector<GLenum>& buffers)
{
    if(m_fbo != 0 && buffers.size() > 0)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
        glViewport(0, 0, static_cast<int>(m_width), static_cast<int>(m_height));

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDrawBuffers(static_cast<int>(buffers.size()), &buffers[0]);
    }
}

void Texture::bind(const uint32_t& index)
{
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
}
}
