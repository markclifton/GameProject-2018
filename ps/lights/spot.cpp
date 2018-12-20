#include "spot.h"

#include <string>

namespace ps
{
namespace lights
{
void setLights(const std::vector<SpotLight>& lights, Shader* shader, glm::mat4 view)
{
    if(shader == nullptr)
    {
        return;
    }

    shader->bind();
    shader->setUniform("spotlightCount", static_cast<int>(lights.size()));
    for(size_t i=0; i<lights.size(); i++)
    {
        std::string uniformNameBase = "spotlights[" + std::to_string(i) + "].";
        shader->setUniform(uniformNameBase + "plight.light.color", lights[i].color);
        shader->setUniform(uniformNameBase + "plight.light.intensity", lights[i].intensity);
        shader->setUniform(uniformNameBase + "plight.elc", lights[i].elc);

        glm::vec4 pos = view * glm::vec4(lights[i].pos_w, 1);
        shader->setUniform(uniformNameBase + "plight.pos_w", glm::vec3(pos.x, pos.y, pos.z));

        glm::vec4 dir = view * glm::vec4(lights[i].direction, 0);
        shader->setUniform(uniformNameBase + "direction", glm::vec3(dir.x, dir.y, dir.z));
        shader->setUniform(uniformNameBase + "cutoff", lights[i].cutoff);
    }
}
}
}
