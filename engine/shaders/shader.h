#pragma once

#include "glad/gl.h"
#include <glm/mat4x4.hpp>

#include <string>

class Shader
{
public:
    Shader(const std::string& vs, const std::string& fs);
    ~Shader();

    void bind();
    int getAttribLocation(const std::string& attribName);

    void setUniform(const std::string& uniformName, const glm::mat4& matrix);
    void setUniform(const std::string& uniformName, const glm::vec3& vec);
    void setUniform(const std::string& uniformName, const glm::vec4& vec);
    void setUniform(const std::string& uniformName, const int& value);
    void setUniform(const std::string& uniformName, const float& value);
    void setUniform(const std::string& uniformName, const int& size, const int* data);
    void setUniform(const std::string& uniformName, const int& size, const GLuint* data);

private:
    bool compile(const std::string& vs, const std::string& fs);
    void create(const GLuint& vert, const GLuint& frag);

    GLuint m_program;
};
