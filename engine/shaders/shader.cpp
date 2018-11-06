#include "shader.h"

#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

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

int Shader::getAttribLocation(const std::string& attribName)
{
    bind();
    return glGetAttribLocation(m_program, attribName.c_str());
}

void Shader::setUniform(const std::string& uniformName, const glm::mat4& matrix)
{
    auto uniform = glGetUniformLocation(m_program, uniformName.c_str());
    if( uniform != -1 )
    {
        glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(matrix));
    }
}

void Shader::setUniform(const std::string& uniformName, const glm::vec3& vec)
{
    auto uniform = glGetUniformLocation(m_program, uniformName.c_str());
    if( uniform != -1 )
    {
        glUniform3fv(uniform, 1, glm::value_ptr(vec));
    }
}

void Shader::setUniform(const std::string& uniformName, const glm::vec4& vec)
{
    auto uniform = glGetUniformLocation(m_program, uniformName.c_str());
    if( uniform != -1 )
    {
        glUniform4fv(uniform, 1, glm::value_ptr(vec));
    }
}

void Shader::setUniform(const std::string& uniformName, const int& value)
{
    auto uniform = glGetUniformLocation(m_program, uniformName.c_str());
    if( uniform != -1 )
    {
        glUniform1i(uniform, value);
    }
}

void Shader::setUniform(const std::string& uniformName, const float& value)
{
    auto uniform = glGetUniformLocation(m_program, uniformName.c_str());
    if( uniform != -1 )
    {
        glUniform1f(uniform, value);
    }
}

void Shader::setUniform(const std::string& uniformName, const int& size, const int* data)
{
    auto uniform = glGetUniformLocation(m_program, uniformName.c_str());
    if( uniform != -1 )
    {
        glUniform1iv(uniform, size, data);
    }
}

void Shader::setUniform(const std::string& uniformName, const int& size, const GLuint* data)
{
    auto uniform = glGetUniformLocation(m_program, uniformName.c_str());
    if( uniform != -1 )
    {
        glUniform1uiv(uniform, size, data);
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
        GLint log_length;
        glGetShaderiv(vert, GL_INFO_LOG_LENGTH, &log_length);
        std::vector<char> v(static_cast<size_t>(log_length));
        glGetShaderInfoLog(vert, log_length, nullptr, v.data());
        std::string err(begin(v), end(v));

        glDeleteShader(vert);
        std::cerr << "Failed to compile vertex shader: " << err << std::endl;
        return false;
    }

    GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fs_cstr, nullptr);
    glCompileShader(frag);
    glGetShaderiv(frag, GL_COMPILE_STATUS, & Compiled);
    if (!Compiled)
    {
        GLint log_length;
        glGetShaderiv(frag, GL_INFO_LOG_LENGTH, &log_length);
        std::vector<char> v(static_cast<size_t>(log_length));
        glGetShaderInfoLog(frag, log_length, nullptr, v.data());
        std::string err(begin(v), end(v));

        glDeleteShader(vert);
        std::cerr << "Failed to compile fragment shader: " << err << std::endl;
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
