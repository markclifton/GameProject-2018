#pragma once

#include <string>

#include "drawableobject.h"

namespace drawable
{
class Model : public DrawableObject
{
public:
    Model(const std::string& path, Shader* shader);
    void draw(glm::mat4 transform = glm::mat4(1.f)) override;

private:
    void loadModel();
    std::string m_path {""};
};
}
