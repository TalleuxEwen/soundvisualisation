//
// Created by talleux on 2/15/24.
//

#include "SessionProperties.hpp"

void SessionProperties::setSurfaceSize(int width, int height)
{
    surfaceSize = {width, height};
}

void SessionProperties::addSpeaker(int x, int y, DIRECTION direction)
{
    speakers.emplace_back(x, y, direction);
    obstacles.emplace_back(x, y);
}

std::tuple<int, int> SessionProperties::getSurfaceSize() const
{
    return surfaceSize;
}

std::vector<std::tuple<int, int, DIRECTION>> SessionProperties::getSpeakers() const
{
    return speakers;
}

void SessionProperties::addObstacle(int x, int y)
{
    obstacles.emplace_back(x, y);
}

std::vector<std::pair<int, int>> SessionProperties::getObstacles() const
{
    return obstacles;
}
