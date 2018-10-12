#pragma once

#include <GL/glew.h>

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

    GLuint m_vertId;
    GLuint m_fragId;
    GLuint m_program;
};
