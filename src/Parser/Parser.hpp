//
// Created by talleux on 2/15/24.
//

#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <memory>
#include "../SessionProperties/SessionProperties.hpp"

enum MODE {
    LOCAL,
    REMOTE
};

class Parser {
    public:
        Parser() = default;
        ~Parser() = default;
        void loadFile(const std::string &filename);
        void parseContent();
        void parseLine(const std::string &line);

        std::shared_ptr<SessionProperties> getSessionProperties();

        void parseArguments(int argc, char **argv);

        std::string getFilename() const;

        MODE getMode() const;

    private:
        std::string _filename;
        std::vector<std::string> _content;
        std::string _line;
        std::string _word;
        std::string _delimiter = " ";
        std::shared_ptr<SessionProperties> _sessionProperties = std::make_shared<SessionProperties>();
        MODE _mode;
};
