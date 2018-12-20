#include "point.h"

#include <string>

namespace ps
{
namespace lights
{
void setLights(const std::vector<PointLight>& lights, Shader* shader, glm::mat4 view)
{
    if(shader == nullptr)
    {
        return;
    }

    shader->bind();
    shader->setUniform("pointlightCount", static_cast<int>(lights.size()));
    for(size_t i=0; i<lights.size(); i++)
    {
        std::string uniformNameBase = "pointlights[" + std::to_string(i) + "].";
        shader->setUniform(uniformNameBase + "light.color", lights[i].color);
        shader->setUniform(uniformNameBase + "light.intensity", lights[i].intensity);
        shader->setUniform(uniformNameBase + "elc", lights[i].elc);

        glm::vec4 pos = view * glm::vec4(lights[i].pos_w, 1);
        shader->setUniform(uniformNameBase + "pos_w", glm::vec3(pos.x, pos.y, pos.z));
    }
}
}
}
