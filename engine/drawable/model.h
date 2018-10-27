#pragma once

// V x y z
// F v1 v2 v3

#include <fstream>
#include <string>

#include "buffers/indexbuffer.h"
#include "buffers/vertexbuffers/vb_basic.h"
#include "drawableobject.h"

/*
 * v 0 0 0
 * v 1 0 0
 * v 1 1 0
 *
 * vn
 * vt
 *
 * //
 * f 1 2 3
 *
 * //
 * f 1/1 2/2 3/3
 *
 * //
 * f 1//1 2//2 3//3
 *
 * //
 * f 1/1/1 2/2/2 3/3/3
 *
 */



namespace drawable
{
    class Model : public DrawableObject
    {
    public:
        Model(const std::string& path, Shader* shader)
            : DrawableObject(shader)
            , m_path(path)
        {
            loadModel();
        }

        void draw(glm::mat4 transform = glm::mat4(1.f)) override
        {
            if(m_shader != nullptr)
            {
                m_shader->bind();
                m_shader->setUniform("transform", transform);
            }

            // TODO: FIX ME (Not Needed)
            buffers::IndexBuffer i;
            i.buffer(static_cast<long>(m_indices.size()*sizeof(GLint)), reinterpret_cast<void*>(&m_indices.front()));

            // TODO: FIX ME (Not Needed)
            buffers::BasicVBO v;
            v.buffer(static_cast<long>(m_vertices.size()*sizeof(Vertex)), reinterpret_cast<void*>(&m_vertices.front()));

            glDrawElements(GL_TRIANGLES, static_cast<int>(m_indices.size()), GL_UNSIGNED_INT, nullptr);
        }
    private:
        std::string m_path {""};

        //TODO: Move to cpp
        //TODO: Make more robust
        void loadModel()
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

    };
}
