//
// Created by talleux on 2/16/24.
//

#include "Session.hpp"

#include <utility>
#include <menu.h>
#include <cmath>

void Session::loadFromProperties(std::shared_ptr<SessionProperties> sessionProperties) {
    _sessionProperties = std::move(sessionProperties);

    loadMap(std::get<0>(_sessionProperties->getSurfaceSize()), std::get<1>(_sessionProperties->getSurfaceSize()));

    for (const auto &speaker : _sessionProperties->getSpeakers()) {
        loadSpeaker(std::get<0>(speaker), std::get<1>(speaker), std::get<2>(speaker));
    }
}

void Session::loadMap(int width, int height) {
    _map.resize(height);
    for (int i = 0; i < height; i++) {
        _map[i].resize(width, ".");
    }
}

void Session::loadSpeaker(int x, int y, DIRECTION direction) {
    switch (direction) {
        case UP:
            _map[y][x] = 'v';
            break;
        case DOWN:
            _map[y][x] = '^';
            break;
        case LEFT:
            _map[y][x] = '>';
            break;
        case RIGHT:
            _map[y][x] = '<';
            break;
    }
}

void Session::display()
{
    for (const auto &row : _map) {
        for (const auto &cell : row) {
            std::cout << cell;
        }
        std::cout << std::endl;
    }
}

void Session::createValuesMap() {
    _valuesMap.resize(_map.size());
    for (int i = 0; i < _map.size(); i++) {
        _valuesMap[i].resize(_map[i].size(), 0);
    }

    for (int i = 0; i < _map.size(); i++) {
        for (int j = 0; j < _map[i].size(); j++) {
            if (_map[i][j] == ".") {
                _valuesMap[i][j] = 0;
            } else {
                _valuesMap[i][j] = -1;
            }
        }
    }
}

void Session::updateFromValuesMap()
{
    for (int i = 0; i < _map.size(); i++) {
        for (int j = 0; j < _map[i].size(); j++) {
            if (_valuesMap[i][j] != -1) {
                if (_valuesMap[i][j] >= 10) {
                    _map[i][j] = 'A';
                } else {
                    _map[i][j] = std::to_string(_valuesMap[i][j])[0];
                }
            }
        }
    }
}

void Session::processValuesDistribution()
{
    for (int i = 0; i < _map.size(); i++) {
        for (int j = 0; j < _map[i].size(); j++) {
            if (_map[i][j] == "v") {
                if (i - 1 >= 0) {
                    _valuesMap[i - 1][j] = 10;
                    propagateValues(j, i - 1, 10, UP);
                }
            } else if (_map[i][j] == "^") {
                if (i + 1 < _map.size()) {
                    _valuesMap[i + 1][j] = 10;
                    propagateValues(j, i + 1, 10, DOWN);
                }
            } else if (_map[i][j] == ">") {
                if (j - 1 >= 0) {
                    _valuesMap[i][j - 1] = 10;
                    propagateValues(j - 1, i, 10, LEFT);
                }
            } else if (_map[i][j] == "<") {
                if (j + 1 < _map[i].size()) {
                    _valuesMap[i][j + 1] = 10;
                    propagateValues(j + 1, i, 10, RIGHT);
                }
            }
        }
    }
}

void Session::propagateValues(int x, int y, int value, DIRECTION direction)
{
    if (direction == UP) {
        if (y - 1 >= 0 && _valuesMap[y - 1][x] < value - 1) {
            if (_valuesMap[y - 1][x] != -1) {
                _valuesMap[y - 1][x] = value - 1;
                propagateValues(x, y - 1, value - 1, UP);
            }
        }
        if (x - 1 >= 0 && _valuesMap[y][x - 1] < value - 1) {
            if (_valuesMap[y][x - 1] != -1) {
                _valuesMap[y][x - 1] = value - 1;
                propagateValues(x - 1, y, value - 1, LEFT);
            }
        }
        if (x + 1 < _valuesMap[y].size() && _valuesMap[y][x + 1] < value - 1) {
            if (_valuesMap[y][x + 1] != -1) {
                _valuesMap[y][x + 1] = value - 1;
                propagateValues(x + 1, y, value - 1, RIGHT);
            }
        }
    } else if (direction == DOWN) {
        if (y + 1 < _valuesMap.size() && _valuesMap[y + 1][x] < value - 1) {
            if (_valuesMap[y + 1][x] != -1) {
                _valuesMap[y + 1][x] = value - 1;
                propagateValues(x, y + 1, value - 1, DOWN);
            }
        }
        if (x - 1 >= 0 && _valuesMap[y][x - 1] < value - 1) {
            if (_valuesMap[y][x - 1] != -1) {
                _valuesMap[y][x - 1] = value - 1;
                propagateValues(x - 1, y, value - 1, LEFT);
            }
        }
        if (x + 1 < _valuesMap[y].size() && _valuesMap[y][x + 1] < value - 1) {
            if (_valuesMap[y][x + 1] != -1) {
                _valuesMap[y][x + 1] = value - 1;
                propagateValues(x + 1, y, value - 1, RIGHT);
            }
        }
    } else if (direction == LEFT) {
        if (x - 1 >= 0 && _valuesMap[y][x - 1] < value - 1) {
            if (_valuesMap[y][x - 1] != -1) {
                _valuesMap[y][x - 1] = value - 1;
                propagateValues(x - 1, y, value - 1, LEFT);
            }
        }
        if (y - 1 >= 0 && _valuesMap[y - 1][x] < value - 1) {
            if (_valuesMap[y - 1][x] != -1) {
                _valuesMap[y - 1][x] = value - 1;
                propagateValues(x, y - 1, value - 1, UP);
            }
        }
        if (y + 1 < _valuesMap.size() && _valuesMap[y + 1][x] < value - 1) {
            if (_valuesMap[y + 1][x] != -1) {
                _valuesMap[y + 1][x] = value + 1;
                propagateValues(x, y + 1, value + 1, DOWN);
            }
        }
    } else if (direction == RIGHT) {
        if (x + 1 < _valuesMap[y].size() && _valuesMap[y][x + 1] < value - 1) {
            if (_valuesMap[y][x + 1] != -1) {
                _valuesMap[y][x + 1] = value - 1;
                propagateValues(x + 1, y, value - 1, RIGHT);
            }
        }
        if (y - 1 >= 0 && _valuesMap[y - 1][x] < value - 1) {
            if (_valuesMap[y - 1][x] != -1) {
                _valuesMap[y - 1][x] = value - 1;
                propagateValues(x, y - 1, value - 1, UP);
            }
        }
        if (y + 1 < _valuesMap.size() && _valuesMap[y + 1][x] < value - 1) {
            if (_valuesMap[y + 1][x] != -1) {
                _valuesMap[y + 1][x] = value - 1;
                propagateValues(x, y + 1, value - 1, DOWN);
            }
        }
    }
}

void Session::colorizeMap()
{
    // red is high value and blue is low value
    // we will use the 256 color mode
    // colors will be gradient from 1 to 10 between red and blue
    for (int i = 0; i < _map.size(); i++) {
        for (int j = 0; j < _map[i].size(); j++) {
            if (_valuesMap[i][j] != -1) {
                // 100 is 255 and -100 is 0
                int colour = 100 - (10 * _valuesMap[i][j]);
                int percent = 255 * colour / 100;
                _map[i][j] = color(255-percent, 0, percent) + " " + resetColor();
            } else {
                _map[i][j] = _map[i][j];
            }
        }
    }

}
