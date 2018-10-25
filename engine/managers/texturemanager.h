#pragma once

#include "glad/gl.h"
#include <FreeImage.h>

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace managers
{
    //TODO: not thread-safe
    struct TextureHandle
    {
        TextureHandle(std::string name, int position)
            : name(name), position(position)
        {}
        std::string name;
        int position {-1};
    };

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

        std::weak_ptr<TextureHandle> bind(const std::string& name);
        void reset();

    private:
        bool unload(const std::string& name);
        GLuint find(const std::string& name);

    protected:
        TextureManager(const TextureManager& tm) = delete;
        TextureManager& operator=(const TextureManager& tm) = delete;

        std::vector<std::pair<std::string, GLuint>> m_textures;
        std::vector<std::shared_ptr<TextureHandle>> m_enabledTextures; //Could be more than 16 textures at some point in the future...
    };
}
