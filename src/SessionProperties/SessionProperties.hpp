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

        void addSpeaker(int x, int y, DIRECTION direction, double loudness, std::vector<int> channels);

        std::tuple<int, int> getSurfaceSize() const;

        std::vector<std::tuple<int, int, DIRECTION, double, std::vector<int>>> getSpeakers() const;

        void addObstacle(int x, int y);

        std::vector<std::pair<int, int>> getObstacles() const;

        void setSpeakerLoudness(int index, double loudness);

    private:
        std::tuple<int, int> surfaceSize;
        std::vector<std::tuple<int, int, DIRECTION, double, std::vector<int>>> speakers;
        std::vector<std::pair<int, int>> obstacles;
};
