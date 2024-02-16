//
// Created by talleux on 2/16/24.
//

#include "Session.hpp"

#include <utility>
#include <menu.h>

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
        _map[i].resize(width, ' ');
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
