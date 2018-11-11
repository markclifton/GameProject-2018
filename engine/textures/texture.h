#pragma once

#include "glad/gl.h"
#include "freeimage/FreeImage.h"

#include <string>

class Texture
{
public:
    Texture(const std::string& name, const std::string& filename, GLenum image_format = GL_RGBA, GLint internal_format = GL_RGBA, GLint level = 0, GLint border = 0);
    ~Texture();
    void bind(const uint32_t& index);

    const std::string& name() { return m_name; }
    const GLuint& id() { return m_textureID; }

private:
    //TODO: replace std::string being used for the name with some other type
    std::string m_name {""};
    GLuint m_textureID {0};
};
