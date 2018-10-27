#include "model.h"

namespace
{
    std::vector<std::string> split(const std::string& s, char seperator)
    {
        std::vector<std::string> output;
        std::string::size_type prev_pos = 0, pos = 0;
        while((pos = s.find(seperator, pos)) != std::string::npos)
        {
            std::string substring( s.substr(prev_pos, pos-prev_pos) );
            output.push_back(substring);
            prev_pos = ++pos;
        }

        output.push_back(s.substr(prev_pos, pos-prev_pos));
        return output;
    }
}

namespace drawable
{
    Model::Model(const std::string& path, Shader* shader)
        : DrawableObject(shader)
        , m_path(path)
    {
        loadModel();
    }

    void Model::draw(glm::mat4 transform)
    {
        if(m_shader != nullptr)
        {
            m_shader->bind();
            m_shader->setUniform("transform", transform);
        }

        if(m_texture)
        {
            m_texture->bind(0);
        }

        m_indicesBuffer.bind();
        m_vertexBuffer.bind();
        if(m_changed)
        {
            m_changed = false;
            m_indicesBuffer.buffer(static_cast<long>(m_indices.size()*sizeof(GLint)), reinterpret_cast<void*>(&m_indices.front()));
            m_vertexBuffer.buffer(static_cast<long>(m_vertices.size()*sizeof(Vertex)), reinterpret_cast<void*>(&m_vertices.front()));
        }

        glDrawElements(GL_TRIANGLES, static_cast<int>(m_indices.size()), GL_UNSIGNED_INT, nullptr);
    }

    void Model::loadModel()
    {
        int faceOffset = std::numeric_limits<int>::max();

        std::ifstream ifs(m_path);
        if (ifs.is_open())
        {
            std::string line;
            while ( getline (ifs, line) )
            {
                std::vector<std::string> ls = split(line, ' ');
                if(ls.size() > 3)
                {
                    if(ls.front().compare("v") == 0)
                    {
                        Vertex v;
                        v.pos = glm::vec3(stof(ls[1]), stof(ls[2]), stof(ls[3]));
                        v.color = glm::vec4(v.pos, 1);
                        m_vertices.push_back(v);
                    }
                    else if(ls.front().compare("f") == 0)
                    {
                        auto v1 = split(ls[1], '/');
                        auto v2 = split(ls[2], '/');
                        auto v3 = split(ls[3], '/');

                        faceOffset = std::min(stoi(v1[0]), faceOffset); //TODO: Improve this

                        m_indices.push_back(stoi(v1[0]));
                        m_indices.push_back(stoi(v2[0]));
                        m_indices.push_back(stoi(v3[0]));
                    }
                    else
                    {
                        //Not handling yet
                    }
                }
            }
            ifs.close();
        }
        else
        {
            //Failed to open
        }

        if(faceOffset > 0)
        {
            for(auto& ind : m_indices)
            {
                ind -= faceOffset;
            }
        }
    }
}
