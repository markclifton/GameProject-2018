#pragma once

#include "glad/gl.h"
#ifdef _WIN32
#include "freeimage/FreeImage.h"
#elif __linux__
#include <FreeImage.h>
#elif __APPLE__
#include "FreeImage.h"
#endif

#include <string>
#include <vector>

namespace ps
{
class Texture
{
public:
    Texture(const std::string& name, const std::string& filename, GLenum image_format = GL_RGBA, GLint internal_format = GL_RGBA, GLint level = 0, GLint border = 0);
    Texture(const std::string& name, int width = 1024, int height = 1024);
    ~Texture();

    void setAsRenderTarget();
    void setAsRenderTarget(const std::vector<GLenum>& buffers);
    void bind(const uint32_t& index);

    const std::string& name() { return m_name; }
    const GLuint& id() { return m_textureID; }


    inline void release()
    {
        if(m_textureID != 0)
        {
            glDeleteTextures(1, &m_textureID);
            m_textureID = 0;
        }

        if(m_fbo != 0)
        {
            glDeleteFramebuffers(1, &m_fbo);
            m_fbo = 0;
        }
    }

private:
    std::string m_name {""};
    GLuint m_textureID {0};
    GLuint m_fbo {0};
    int  m_width {0};
    int  m_height {0};
};
}
