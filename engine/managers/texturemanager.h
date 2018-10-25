#pragma once

#include "glad/gl.h"
#include <FreeImage.h>

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "textures/texture.h"

namespace managers
{
    // TODO: not thread-safe
    class TextureManager
    {
    public:
        TextureManager();
        virtual ~TextureManager();

        //TODO: Make name a uuid or some other identifier, string is horrible.
        void load(const std::string& name,
                         const char* filename,
                         GLenum image_format = GL_RGBA,
                         GLint internal_format = GL_RGBA,
                         GLint level = 0,
                         GLint border = 0);

        bool bind(const std::string& name, uint position = 0);
        void reset();

    private:
        bool unload(const std::string& name);
        std::weak_ptr<Texture> find(const std::string& name); //TODO: no real need for sp yet, ever?

    protected:
        TextureManager(const TextureManager& tm) = delete;
        TextureManager& operator=(const TextureManager& tm) = delete;

        std::vector<std::pair<std::string, std::shared_ptr<Texture>>> m_textures;
    };
}
