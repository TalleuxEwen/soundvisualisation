//
// Created by talleux on 2/15/24.
//

#include "Parser.hpp"

void Parser::loadFile(const std::string &filename)
{
    std::ifstream file(filename);
    std::string line;

    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            _content.push_back(line);
        }
        file.close();
    }
    else
    {
        throw std::runtime_error("File not found");
    }
}

void Parser::parseContent()
{

}
