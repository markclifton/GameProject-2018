#pragma once

#include <string>

#include "ps/ecs/entities/drawableentity.h"

namespace ps
{
namespace drawable
{
class Model : public DrawableEntity
{
public:
    Model(const std::string& context, const std::string& path, Shader* shader);

private:
    void loadModel();
    std::string m_path {""};
};
}
}
