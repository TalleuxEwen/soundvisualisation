//
// Created by talleux on 2/15/24.
//

#pragma once

#include <tuple>
#include <vector>
#include <string>
#include <array>

enum DIRECTION {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

static std::array<std::string, 4> DIRECTION_STR = {
    "up",
    "down",
    "left",
    "right"
};

class SessionProperties {
    public:
        SessionProperties() = default;
        ~SessionProperties() = default;

        void setSurfaceSize(int width, int height);

        void addSpeaker(int x, int y, DIRECTION direction);

    private:
        std::tuple<int, int> surfaceSize;
        std::vector<std::tuple<int, int, DIRECTION>> speakers;
};
