//
// Created by talleux on 2/15/24.
//

#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class Parser {
    public:
        Parser() = default;
        ~Parser() = default;
        void loadFile(const std::string &filename);
        void parseContent();
        void parseLine();

    private:
        std::string _filename;
        std::vector<std::string> _content;
        std::string _line;
        std::string _word;
        std::string _delimiter = " ";
};
