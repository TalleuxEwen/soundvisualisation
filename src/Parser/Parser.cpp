//
// Created by talleux on 2/15/24.
//

#include <sstream>
#include <algorithm>
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
    for (const auto &line : _content)
    {
        if (!line.empty())
            parseLine(line);
    }
}

std::shared_ptr<SessionProperties> Parser::getSessionProperties() const {
    return _sessionProperties;
}

void Parser::parseLine(const std::string &line)
{
    std::vector<std::string> tokens;
    std::string token;

    std::istringstream tokenStream(line);

    while (std::getline(tokenStream, token, ' '))
    {
        tokens.push_back(token);
    }

    if (tokens.size() < 2)
        throw std::runtime_error("Invalid line");

    if (tokens[0] == "surface:") {
        if (tokens.size() != 3)
            throw std::runtime_error("Invalid surface");

        _sessionProperties->setSurfaceSize(std::stoi(tokens[1]), std::stoi(tokens[2]));
    }
    if (tokens[0] == "speaker:") {
        if (tokens.size() != 4)
            throw std::runtime_error("Invalid speaker");

        DIRECTION direction;
        std::string directionToken = tokens[3];
        auto it = std::find(DIRECTION_STR.begin(), DIRECTION_STR.end(), directionToken);
        if (it != DIRECTION_STR.end())
            direction = static_cast<DIRECTION>(std::distance(DIRECTION_STR.begin(), it));
        else
            direction = DIRECTION::DOWN;

        _sessionProperties->addSpeaker(std::stoi(tokens[1]), std::stoi(tokens[2]), direction);
    }
}
