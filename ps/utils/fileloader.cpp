#include "fileloader.h"

#include <fstream>
#include <iostream>

namespace ps
{
namespace utils
{
std::string loadFile(const std::string& path)
{
    std::string result;

    std::ifstream ifs(path);
    if (ifs.is_open())
    {
        std::string line;
        while ( getline (ifs, line) )
        {
            result += line + "\n";
        }
        ifs.close();
    }
    else
    {
        std::cerr << "Failed to open file: " << path << std::endl;
    }
    return result;
}
}
}
