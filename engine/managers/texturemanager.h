#pragma once

#include "glad/gl.h"
#ifdef _WIN32
#include "freeimage/FreeImage.h"
#elif __linux__
#include <FreeImage.h>
#endif

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

    Texture* find(const std::string& name);
    bool bind(const std::string& name, uint32_t position = 0);
    void reset();

private:
    bool unload(const std::string& name); //TODO: Needs tested...

protected:
    TextureManager(const TextureManager& tm) = delete;
    TextureManager& operator=(const TextureManager& tm) = delete;

    std::vector<std::unique_ptr<Texture>> m_textures;
};
}
