#include "shader.h"

#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "utils/fileloader.h"

Shader::Shader(const std::string& vs, const std::string& fs)
{
    if( !compile(vs, fs) )
    {
        std::cerr << "Failed to compile shader\n";
    }
}

Shader::~Shader()
{
    if(m_program != 0)
    {
         glDeleteProgram(m_program);
    }
}

void Shader::bind()
{
    glUseProgram(m_program);
}

void Shader::enableAttribArray(const std::string& attribName)
{
    bind();
    auto attrib = glGetAttribLocation(m_program, attribName.c_str());
    if( attrib != -1 )
    {
        glEnableVertexAttribArray(static_cast<GLuint>(attrib));
    }
}

void Shader::setUniform(const std::string& uniformName, const glm::mat4& matrix)
{
    auto uniform = glGetUniformLocation(m_program, uniformName.c_str());
    if( uniform != -1 )
    {
        glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(matrix));
    }
}

bool Shader::compile(const std::string& vsPath, const std::string& fsPath)
{
    auto vs = utils::loadFile(vsPath);
    auto vs_cstr = vs.c_str();
    auto fs = utils::loadFile(fsPath);
    auto fs_cstr = fs.c_str();

    GLint Compiled;
    GLuint vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vs_cstr, nullptr);
    glCompileShader(vert);
    glGetShaderiv(vert, GL_COMPILE_STATUS, & Compiled);
    if (!Compiled)
    {
        std::cerr << "Failed to compile vertex shader!" << std::endl;
        return false;
    }

    GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fs_cstr, nullptr);
    glCompileShader(frag);
    glGetShaderiv(frag, GL_COMPILE_STATUS, & Compiled);
    if (!Compiled)
    {
        glDeleteShader(vert);
        std::cerr << "Failed to compile fragment shader!" << std::endl;
        return false;
    }

    create(vert, frag);

    glDeleteShader(vert);
    glDeleteShader(frag);

    return true;
}

void Shader::create(const GLuint& vert, const GLuint& frag)
{
    m_program = glCreateProgram(); //Returns a non-zero value
    glAttachShader(m_program, vert);
    glAttachShader(m_program, frag);

    glLinkProgram(m_program);
}
