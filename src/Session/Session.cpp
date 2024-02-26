//
// Created by talleux on 2/16/24.
//

#include "Session.hpp"

#include <cmath>
#include <utility>
#include <menu.h>
#include <cmath>

static bool intersect(double vect0[2], double vect1[2], double diag0[2], double daig1[2], double rect[2]) {

    if (vect1[0] - vect0[0] != 0) {
        double Vecta = (vect1[1] - vect0[1]) / (vect1[0] - vect0[0]);
        double Vectb = vect0[1] - (Vecta * vect0[0]);

        double Diaga = (daig1[1] - diag0[1]) / (daig1[0] - diag0[0]);
        double Diagb = diag0[1] - (Diaga * diag0[0]);

        if (Vecta == Diaga) {
            return false;
        }

        double x = (Diagb - Vectb) / (Vecta - Diaga);
        if (x < vect0[0] || x > vect1[0]) {
            return false;
        }

        if (x < diag0[0] || x > daig1[0]) {
            return false;
        }
    } else if (vect1[0] - vect0[0] == 0) {
        vect0[0] += 0.0001;
        double Vecta = (vect1[1] - vect0[1]) / (vect1[0] - vect0[0]);
        double Vectb = vect0[1] - (Vecta * vect0[0]);

        double Diaga = (daig1[1] - diag0[1]) / (daig1[0] - diag0[0]);
        double Diagb = diag0[1] - (Diaga * diag0[0]);

        if (Vecta == Diaga) {
            return false;
        }

        double x = (Diagb - Vectb) / (Vecta - Diaga);
        if (x < vect0[0] || x > vect1[0]) {
            return false;
        }

        if (x < diag0[0] || x > daig1[0]) {
            return false;
        }
    }

    return true;
}



static bool isBehindObs(double xsource, double ysource, double xobs, double yobs, double xdest, double ydest)
{
    double vect0[2] = {xsource + 0.5, ysource + 0.5};
    double vect1[2] = {xdest + 0.5, ydest + 0.5};
    double rect[2] = {xobs, yobs};

    double recttopLeft[2] = {rect[0], rect[1]};
    double recttopRight[2] = {rect[0] + 1, rect[1]};
    double rectbottomLeft[2] = {rect[0], rect[1] + 1};
    double rectbottomRight[2] = {rect[0] + 1, rect[1] + 1};

    if (intersect(vect0, vect1, recttopLeft, rectbottomRight, rect)) {
        return true;
    }

    if (intersect(vect0, vect1, rectbottomRight, recttopLeft, rect)) {
        return true;
    }

    if (intersect(vect1, vect0, recttopLeft, rectbottomRight, rect)) {
        return true;
    }

    if (intersect(vect1, vect0, rectbottomRight, recttopLeft, rect)) {
        return true;
    }

    if (intersect(vect1, vect0, recttopRight, rectbottomLeft, rect)) {
        return true;
    }

    if (intersect(vect1, vect0, rectbottomLeft, recttopRight, rect)) {
        return true;
    }

    if (intersect(vect0, vect1, rectbottomLeft, recttopRight, rect)) {
        return true;
    }

    return intersect(vect0, vect1, recttopRight, rectbottomLeft, rect);

}

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
            _map[y][x] = resetColor() + "v ";
            break;
        case DOWN:
            _map[y][x] = resetColor() + "^ ";
            break;
        case LEFT:
            _map[y][x] = resetColor() + "> ";
            break;
        case RIGHT:
            _map[y][x] = resetColor() + "< ";
            break;
    }
}

void Session::redisplay()
{
    std::flush(std::cout);
    int height = _map.size();
    std::cout << "\033[" << height << "A";
    std::flush(std::cout);
    for (const auto &row : _map) {
        std::cout << "\r\033[K";
        for (const auto &cell : row) {
            std::cout << cell;
        }
        std::cout << std::endl;
    }
    std::flush(std::cout);
    _map.clear();
}

void Session::display()
{
    for (const auto &row : _map) {
        for (const auto &cell : row) {
            std::cout << cell;
        }
        std::cout << std::endl;
    }
    _map.clear();
}

void Session::createValuesMap() {
    _valuesMap.clear();
    _valuesMap.resize(_map.size());
    for (int i = 0; i < _map.size(); i++) {
        _valuesMap[i].resize(_map[i].size(), 0);
    }

    for (int i = 0; i < _map.size(); i++) {
        for (int j = 0; j < _map[i].size(); j++) {
            if (_map[i][j] == ".") {
                _valuesMap[i][j] = 0;
            } else {
                _valuesMap[i][j] = -4242;
            }
        }
    }
}

void Session::updateFromValuesMap()
{
    for (int i = 0; i < _map.size(); i++) {
        for (int j = 0; j < _map[i].size(); j++) {
            if (_valuesMap[i][j] != -4242) {
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
            if (_map[i][j] == resetColor() + "v ") {
                if (i - 1 >= 0) {
                    _valuesMap[i - 1][j] = 10;
                    propagateValues(j, i - 1, 10, UP);
                }
            } else if (_map[i][j] == resetColor() + "^ ") {
                if (i + 1 < _map.size()) {
                    _valuesMap[i + 1][j] = 10;
                    propagateValues(j, i + 1, 10, DOWN);
                }
            } else if (_map[i][j] == resetColor() + "> ") {
                if (j - 1 >= 0) {
                    _valuesMap[i][j - 1] = 10;
                    propagateValues(j - 1, i, 10, LEFT);
                }
            } else if (_map[i][j] == resetColor() + "< ") {
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
    for (int i = 0; i < _map.size(); i++) {
        for (int j = 0; j < _map[i].size(); j++) {
            if (_valuesMap[i][j] != -4242) {
                for (auto obstacle : _sessionProperties->getObstacles()) {
                    if (i == obstacle.second && j == obstacle.first) {
                        _valuesMap[i][j] = -6969;
                    }
                }
                if (_valuesMap[i][j] == -6969) {
                    continue;
                }
                double oldvalue = _valuesMap[i][j];
                _valuesMap[i][j] = sqrt(pow(x - j, 2) + pow(y - i, 2));
                if (_valuesMap[i][j] == 0) {
                    _valuesMap[i][j] = 0.9;
                }
                double speakerLoudness = getLoudnessBySpeaker(x, y);
                //std::cout << "Speaker loudness: " << speakerLoudness << std::endl;
                _valuesMap[i][j] = speakerLoudness - 20 * log10(_valuesMap[i][j]/1);

                for (auto obstacle : _sessionProperties->getObstacles()) {
                    if (isBehindObs(x, y, obstacle.first, obstacle.second, j, i)) {
                        _valuesMap[i][j] *= 0.85;
                    }
                }
                //std::cout << "Value: " << _valuesMap[i][j] << " at " << i << " " << j << " from " << x << " " << y << " with loudness " << speakerLoudness << " old value: " << oldvalue << std::endl;
                if (oldvalue < 0)
                    _valuesMap[i][j] = _valuesMap[i][j];
                else if (_valuesMap[i][j] < 0)
                    _valuesMap[i][j] = oldvalue;
                else
                    _valuesMap[i][j] = oldvalue + _valuesMap[i][j];

            }
        }
    }
}

void Session::colorizeMap()
{
    int overflow = 0;

    for (int i = 0; i < _map.size(); i++) {
        for (int j = 0; j < _map[i].size(); j++) {
            overflow = 0;
            if (_valuesMap[i][j] != -4242) {
                if (_valuesMap[i][j] == -6969) {
                    _map[i][j] = color(0, 0, 0) + "  " + resetColor();
                } else {
                    int colour = (int) (255 * (_valuesMap[i][j]) / 42);
                    if (colour < 0) {
                        colour = 0;
                    }
                    if (colour > 255) {
                        overflow = colour - 255;
                        colour = 255;
                    }
                    if (overflow > 255) {
                        overflow = 255;
                    }
                    _map[i][j] = color(colour, overflow, 255 - colour) + "  " + resetColor();
                }
            }
        }
    }

}

void Session::setLoudness(double loudness) {
    _loudness = loudness;
}

double Session::getLoudness() const {
    return _loudness;
}

double Session::getLoudnessBySpeaker(int x, int y) const {
    SessionProperties sessionProperties = *_sessionProperties;
    for (const auto &speaker : sessionProperties.getSpeakers()) {
        if (std::get<2>(speaker) == UP) {
            if (std::get<0>(speaker) == x && std::get<1>(speaker) == y + 1) {
                return std::get<3>(speaker);
            }
        }
        if (std::get<2>(speaker) == DOWN) {
            if (std::get<0>(speaker) == x && std::get<1>(speaker) == y - 1) {
                return std::get<3>(speaker);
            }
        }
        if (std::get<2>(speaker) == LEFT) {
            if (std::get<0>(speaker) == x - 1 && std::get<1>(speaker) == y) {
                return std::get<3>(speaker);
            }
        }
        if (std::get<2>(speaker) == RIGHT) {
            if (std::get<0>(speaker) == x + 1 && std::get<1>(speaker) == y) {
                return std::get<3>(speaker);
            }
        }
    }
    return 0;
}
