//
// Created by talleux on 2/16/24.
//

#pragma once

#include <memory>
#include <vector>
#include <iostream>
#include "../SessionProperties/SessionProperties.hpp"
#include "../Colors.hpp"

class Session
{
    public:
        Session() = default;
        ~Session() = default;

        void loadFromProperties(std::shared_ptr<SessionProperties> sessionProperties);

        void loadMap(int width, int height);

        void loadSpeaker(int x, int y, DIRECTION direction);

        void redisplay();
        void display();

        void createValuesMap();

        void processValuesDistribution();

        void propagateValues(int x, int y, int value, DIRECTION direction);

        void updateFromValuesMap();

        void colorizeMap();

        void setLoudness(double loudness);

        double getLoudness() const;


    private:
        std::shared_ptr<SessionProperties> _sessionProperties;
        std::vector<std::vector<std::string>> _map;
        std::vector<std::vector<double>> _valuesMap;
        double _loudness = 42;
};
