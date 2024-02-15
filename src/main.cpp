//
// Created by ewen.talleux on 15/02/2024.
//

#include <iostream>
#include "Parser/Parser.hpp"

int main() {
    std::cout << "Hello World" << std::endl;
    Parser parser;
    parser.loadFile("../src/main.cpp");
    return 0;
}
