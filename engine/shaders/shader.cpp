#include "shader.h"

#include <iostream>

Shader::Shader()
{
    if(compile())
    {
        create();
        use();
    }
}

Shader::~Shader()
{
    if(m_program != 0)
    {
        glDeleteProgram(m_program);
    }
}

void Shader::use()
{
    glUseProgram(m_program);

    GLint PositionAttribute = (glGetAttribLocation(m_program, "position"));
    glEnableVertexAttribArray(static_cast<GLuint>(PositionAttribute));

    GLint ColorAttribute = (glGetAttribLocation(m_program, "color"));
    glEnableVertexAttribArray(static_cast<GLuint>(ColorAttribute));
}

bool Shader::compile()
{
    //TODO: Read this in from a shader file, and switch to newer shaders
    char const * VertexShaderSource = R"GLSL(
        #version 130
        in vec3 position;
        in vec3 color;
        out vec3 f_color;
        void main()
        {
            f_color = color;
            gl_Position = vec4(position, 1.0);
        }
    )GLSL";

    char const * FragmentShaderSource = R"GLSL(
        #version 130
        in vec3 f_color;
        out vec4 outColor;
        void main()
        {
            outColor = vec4(f_color, 1.0);
        }
    )GLSL";

    GLint Compiled;
    m_vertId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_vertId, 1, &VertexShaderSource, nullptr);
    glCompileShader(m_vertId);
    glGetShaderiv(m_vertId, GL_COMPILE_STATUS, & Compiled);
    if (! Compiled)
    {
        std::cerr << "Failed to compile vertex shader!" << std::endl;
        return false;
    }

    m_fragId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_fragId, 1, &FragmentShaderSource, nullptr);
    glCompileShader(m_fragId);
    glGetShaderiv(m_fragId, GL_COMPILE_STATUS, & Compiled);
    if (!Compiled)
    {
        glDeleteShader(m_vertId);
        std::cerr << "Failed to compile fragment shader!" << std::endl;
        return false;
    }

    return true;
}

void Shader::create()
{
    m_program = glCreateProgram();
    glAttachShader(m_program, m_vertId);
    glAttachShader(m_program, m_fragId);

    glBindFragDataLocation(m_program, 0, "outColor");
    glLinkProgram(m_program);

    glDeleteShader(m_vertId);
    glDeleteShader(m_fragId);

}
