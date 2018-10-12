#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

class Shader
{
public:
    Shader();
    ~Shader();
    void use();

private:
    bool compile();
    void create();

    std::string m_vert;
    GLuint m_vertId;

    std::string m_frag;
    GLuint m_fragId;

    GLuint m_program;
};
