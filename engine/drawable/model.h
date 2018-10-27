#pragma once

// V x y z
// F v1 v2 v3

#include <fstream>
#include <string>

#include "buffers/indexbuffer.h"
#include "buffers/vertexbuffers/vb_basic.h"
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
