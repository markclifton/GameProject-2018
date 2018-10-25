#pragma once

#include "glad/gl.h"

#include <string>

#include <FreeImage.h>

class Texture
{
public:
    Texture(const std::string& path);
    ~Texture();
    bool bind(const uint& index);

    GLuint id() { return m_textureID; }

private:
    bool load(const char* filename, GLenum image_format = GL_RGBA, GLint internal_format = GL_RGBA, GLint level = 0, GLint border = 0);

    GLuint m_textureID {0};
};
