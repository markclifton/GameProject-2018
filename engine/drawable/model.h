#pragma once

#include <string>

#include "drawableobject.h"

namespace drawable
{
class Model : public DrawableObject
{
public:
    Model(const std::string& path, Shader* shader);

private:
    void loadModel();
    std::string m_path {""};
};
}
