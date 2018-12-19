#include <glm/vec3.hpp>

#include <vector>

#include "shaders/shader.h"

namespace ps
{
namespace lights
{
struct SpotLight
{
    glm::vec3 color;
    float intensity;
    glm::vec3 elc;
    glm::vec3 pos_w;
    glm::vec3 direction;
    float cutoff;
};

void setLights(const std::vector<SpotLight>& lights, Shader* shader, glm::mat4 view);
}
}
