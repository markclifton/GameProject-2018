#pragma once

#include <string>

#include "ecs/entities/drawableentity.h"

namespace drawable
{
class Model : public DrawableEntity
{
public:
    Model(const std::string& path, Shader* shader);

private:
    void loadModel();
    std::string m_path {""};
};
}
