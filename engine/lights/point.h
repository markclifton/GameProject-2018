#include <glm/vec3.hpp>

#include <vector>

#include "shaders/shader.h"

namespace ps
{
namespace lights
{
struct PointLight
{
    glm::vec3 color;
    float intensity;
    glm::vec3 elc;
    glm::vec3 pos_w;
};

void setLights(const std::vector<PointLight>& lights, Shader* shader, glm::mat4 view);
}
}
