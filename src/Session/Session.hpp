//
// Created by talleux on 2/16/24.
//

#pragma once

#include <memory>
#include "../SessionProperties/SessionProperties.hpp"

class Session
{
    public:
        Session() = default;
        ~Session() = default;

        void loadFromProperties(std::shared_ptr<SessionProperties> sessionProperties);

        void loadMap(int width, int height);

        void loadSpeaker(int x, int y, DIRECTION direction);

    private:
        std::shared_ptr<SessionProperties> _sessionProperties;
        std::vector<std::vector<char>> _map;
};
