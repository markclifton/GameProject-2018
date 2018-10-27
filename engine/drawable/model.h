#pragma once

// V x y z
// F v1 v2 v3

#include <fstream>
#include <string>

#include "buffers/indexbuffer.h"
#include "buffers/vertexbuffers/vb_basic.h"
#include "drawableobject.h"

/*
 * v 0 0 0
 * v 1 0 0
 * v 1 1 0
 *
 * vn
 * vt
 *
 * //
 * f 1 2 3
 *
 * //
 * f 1/1 2/2 3/3
 *
 * //
 * f 1//1 2//2 3//3
 *
 * //
 * f 1/1/1 2/2/2 3/3/3
 *
 */

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
