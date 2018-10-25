#pragma once

#include <glm/matrix.hpp>

#include <iostream>

#include "managers/texturemanager.h"
#include "shaders/shader.h"
#include "textures/texture.h"


namespace drawable
{
    //TODO: Remove "inlines" from header
    // Drawable can have a draw called upon it
    class Drawable
    {
    public:
        Drawable(Shader* shader) : m_shader( shader ) {}
        virtual ~Drawable() = default;
        virtual void draw(glm::mat4 transform = glm::mat4(1.f)) = 0;

        virtual void setTransform(glm::mat4 transform)
        {
            m_transform = transform;
        }

        inline bool setTexture(const std::string& path)
        {
            if(m_textures.size() > 16 )
            {
                return false;
            }

            auto newTexture = std::make_unique<Texture>(path);
            if( newTexture == nullptr )
            {
                return false;
            }

            m_textures.push_back(std::move(newTexture));
            return true;
        }

        //TEMP
        glm::mat4 m_transform {1.f};
    protected:
        Shader* m_shader;
        std::vector<std::unique_ptr<Texture>> m_textures;
    };
}
