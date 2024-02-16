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

        std::tuple<int, int> getSurfaceSize() const;

        std::vector<std::tuple<int, int, DIRECTION>> getSpeakers() const;

    private:
        std::tuple<int, int> surfaceSize;
        std::vector<std::tuple<int, int, DIRECTION>> speakers;
};
