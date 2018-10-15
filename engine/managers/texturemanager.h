#pragma once

#include "glad/gl.h"
#include <FreeImage.h>

#include <map>
#include <string>
#include <vector>

namespace managers
{
    // TODO: not thread-safe
    class TextureManager
    {
    public:
        TextureManager();
        virtual ~TextureManager();

        bool load(const std::string& name,
                         const char* filename,
                         GLenum image_format = GL_RGBA,
                         GLint internal_format = GL_RGBA,
                         GLint level = 0,
                         GLint border = 0);

        bool bind(const std::string& name);
        bool unload(const std::string& name);
        void reset();

        GLuint find(const std::string& name);

    protected:
        TextureManager(const TextureManager& tm) = delete;
        TextureManager& operator=(const TextureManager& tm) = delete;

        std::vector<std::pair<std::string, GLuint>> m_textures;
    };
}
